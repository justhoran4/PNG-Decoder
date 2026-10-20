#ifndef PNG_DECODER_DECODE_PNG_H
#define PNG_DECODER_DECODE_PNG_H

#include "png_err_types.h"
#include "fil_ops.h"

/*******************************************************
CONSTANTS
*******************************************************/
#define PNG_SIGNATURE   ( 0x89504E470D0A1A0AULL ) 
#define SIG_SZ          ( 8 )

#define CHNK_FLD_LEN_SZ     ( 4 )
#define CHNK_FLD_TYPE_SZ    ( 4 )
#define CHNK_FLD_CRC_SZ     ( 4 )

#define MAX_CHNK_LEN    (0x8000000) /* 2GB */

/* Critical Chunks      */
#define IHDR_CHNK_TYPE  "IHDR"
#define PLTE_CHNK_TYPE  "PLTE"
#define IDAT_CHNK_TYPE  "IDAT"
#define IEND_CHNK_TYPE  "IEND"

/* Ancillary chunks     */
#define CHRM_CHNK_TYPE  "cHRM"
#define GAMA_CHNK_TYPE  "gAMA"
#define ICCP_CHNK_TYPE  "iCCP"
#define SBIT_CHNK_TYPE  "sBIT"
#define SRGB_CHNK_TYPE  "sRGB"
#define BKGD_CHNK_TYPE  "bKGD"
#define HIST_CHNK_TYPE  "hIST"
#define TRNS_CHNK_TYPE  "tRNS"
#define PHYS_CHNK_TYPE  "pHYs"
#define SPLT_CHNK_TYPE  "sPLT"
#define TIME_CHNK_TYPE  "tIME"
#define ITXT_CHNK_TYPE  "iTXt"
#define TEXT_CHNK_TYPE  "tEXt"
#define ZTXT_CHNK_TYPE  "zTXt"

#define PLTE_ENT_SZ     ( 3 )

#define ICCP_PROF_NAME_LEN  ( 79 )
#define TEXT_KEYWRD_LEN     ( 79 )
#define PLTE_NAME_LEN       ( 79 )

/*******************************************************
MACROS
*******************************************************/
#define get_chunk_mask( chunk )     ( 1 << ( chunk ) )

/*******************************************************
TYPES
*******************************************************/
typedef uint8   chnk_type_t8;
enum
    {
    /***************************************************
    Critical Chunks
    ***************************************************/
    CHNK_TYPE_IHDR,
    CHNK_TYPE_PLTE,
    CHNK_TYPE_IDAT,
    CHNK_TYPE_IEND,
    CHNK_TYPE_CRIT_CHNKS = CHNK_TYPE_IEND,

    /***************************************************
    Ancillary Chunks
    ***************************************************/
    CHNK_TYPE_ANCC_FIRST,
    CHNK_TYPE_CHRM = CHNK_TYPE_ANCC_FIRST,
    CHNK_TYPE_GAMA,
    CHNK_TYPE_ICCP,
    CHNK_TYPE_SBIT,
    CHNK_TYPE_SRGB,
    CHNK_TYPE_BKGD,
    CHNK_TYPE_HIST,
    CHNK_TYPE_TRNS,
    CHNK_TYPE_PHYS,
    CHNK_TYPE_SPLT,
    CHNK_TYPE_TIME,
    CHNK_TYPE_ITXT,
    CHNK_TYPE_TEXT,
    CHNK_TYPE_ZTXT,
    CHNK_TYPE_ANCC_LAST = CHNK_TYPE_ZTXT,
    CHNK_TYPE_CNT,
    CHNK_TYPE_INVALID = CHNK_TYPE_CNT
    };

#pragma pack(push, 1)
typedef struct chnk_layout_t
    {
    uint32  length;
    char    type[ CHNK_FLD_TYPE_SZ + 1 ]; /* Account for NULL terminator */
    uint32  crc;
    } chnk_layout;

/*******************************************************
Defined Chunk Types
*******************************************************/

typedef struct decoder_ihdr_chnk_t
    {
    uint32  width;
    uint32  height;
    uint8   bit_depth;
    uint8   color_type;
    uint8   compression_method;
    uint8   filter_method;
    uint8   interlace_method;
    } decoder_ihdr_chnk;

typedef struct decoder_idat_chnk_t
    {
    uint8 * data;
    } decoder_idat_chnk;

typedef struct decoder_plte_chnk_t
    {
    uint8         * plt_data;
    } decoder_plte_chnk;

typedef struct decoder_trns_chnk_t
    {
    uint16  gryscl;
    uint64  trucolor; /* TODO: make struct of 3 shorts for RGB */
    uint8 * idxed_color; 
    } decoder_trns_chnk;

typedef struct decoder_gama_chnk_t
    {
    uint32  gamma;
    } decoder_gama_chnk;

typedef struct decoder_chrm_chnk_t
    {
    uint32  wht_pt_x;
    uint32  wht_pt_y;
    uint32  red_x;
    uint32  red_y;
    uint32  green_x;
    uint32  green_y;
    uint32  blue_x;
    uint32  blue_y;
    } decoder_chrm_chnk;

typedef struct decoder_srgb_chnk_t
    {
    uint8   rndr_intent;
    } decoder_srgb_chnk;

typedef struct decoder_iccp_chnk_t
    {
    uint8   prof_name[ ICCP_PROF_NAME_LEN ];
    uint8   null_sep;
    uint8   cmprs_mthd;
    uint8 * cmprs_prof; /* TODO: specification says 'n' bytes; need more info */
    } decoder_iccp_chnk;

typedef struct decoder_text_chnk_t
    {
    uint8   keyword[ TEXT_KEYWRD_LEN ];
    uint8   null_sep;
    uint8 * text;
    } decoder_text_chnk;
    
typedef struct decoder_ztxt_chnk_t
    {
    uint8   keyword[ TEXT_KEYWRD_LEN ];
    uint8   null_sep;
    uint8   cmprs_mthd;
    uint8 * cmprs_text;
    } decoder_ztxt_chnk;

typedef struct decoder_itxt_chnk_t
    {
    uint8   keyword[ TEXT_KEYWRD_LEN ];
    uint8   null_sep;
    uint8   cmprs_flag;
    uint8   cmprs_mthd;
    uint8 * lang_tag;
    uint8   null_sep_lang_tag;
    uint8 * trnsltd_keyword;
    uint8   null_sep_trnsltd_keyword;
    uint8 * text;
    } decoder_itxt_chnk;

typedef struct decoder_bkgd_chnk_t
    {
    uint8   plte_idx;
    uint16  gray_scl;
    uint16  red;
    uint16  green;
    uint16  blue;
    } decoder_bkgd_chnk;

typedef struct decoder_phys_chnk_t
    {
    uint32  pxl_per_unit_x;
    uint32  pxl_per_unit_y;
    uint8   unit_spec;
    } decoder_phys_chnk;

typedef struct decoder_sbit_chnk_t
    {
    uint8   bits;
    } decoder_sbit_chnk;

typedef struct decoder_splt_chnk_t
    {
    uint8   plte_name[ PLTE_NAME_LEN ];
    uint8   null_term;
    uint8   samp_dpth;
    uint16  red;
    uint16  green;
    uint16  blue;
    uint16  alpha;
    uint16  freq;
    } decoder_splt_chnk;

typedef struct decoder_hist_chnk_t
    {
    uint16 * freq_series;
    } decoder_hist_chnk;

typedef struct decoder_time_chnk_t
    {
    uint16  year;
    uint8   month;
    uint8   day;
    uint8   hour;
    uint8   min;
    uint8   sec;
    } decoder_time_chnk;

typedef chnk_layout decoder_iend_chnk;

#pragma pack(pop)

/* TODO Add Chunk extensions later */

/*******************************************************
End Defined Chunk Types
*******************************************************/

typedef union decoder_chnk_types_t
    {
    decoder_ihdr_chnk  ihdr;
    decoder_plte_chnk  plte;
    decoder_idat_chnk  idat;
    decoder_chrm_chnk  chrm;
    decoder_gama_chnk  gama;
    decoder_iccp_chnk  iccp;
    decoder_sbit_chnk  sbit;
    decoder_srgb_chnk  srgb;
    decoder_hist_chnk  hist;
    decoder_trns_chnk  trns;
    decoder_phys_chnk  phys;
    decoder_splt_chnk  splt;
    decoder_time_chnk  time;
    decoder_itxt_chnk  itxt;
    decoder_text_chnk  text;
    decoder_ztxt_chnk  ztxt;
    } decoder_chnk_types;

typedef struct decoder_node_chnk_t /* list of chunks between IDAT and IEND */
    {
    chnk_layout         hdr;
    decoder_chnk_types   chnk;
    struct decoder_node_chnk_t
                      * prev;
    struct decoder_node_chnk_t
                      * next;
    } decoder_node_chnk;

typedef uint8 decode_chnk_mode;
enum
    {
    PARSE_LENGTH,
    PARSE_TYPE,
    PARSE_DATA,
    PARSE_CRC,
    PARSE_INV
    };

typedef struct decoder_ctx_t
    {
    uint8         * buf;
    size_t          fil_len;
    size_t          ofst;
    uint32          chnk_cnt;
    decoder_node_chnk
                  * ihdr_chnk; /* this will serve as the header to the list */
    decoder_node_chnk 
                  * chnk_lst;
    decoder_iend_chnk 
                  * iend;

    /* Mask to keep track of found chunks   */
    uint32          chnk_mask;
    } decoder_ctx;

/*******************************************************
MACROS
*******************************************************/
#define byte_shift_left( x, y ) ( ( x ) << ( y * 8 ) )

#define total_chnk_size( type ) ( sizeof( chnk_layout ) + sizeof( type ) + sizeof( uptr ) )

/*******************************************************
Chunk Table
*******************************************************/
typedef struct chnk_tbl_entry
    {
    chnk_type_t8    chnk_type;
    char            chnk_name[ CHNK_FLD_TYPE_SZ + 1 ];
    uint32          chnk_data_sz;
    size_t          chnk_sz; 
    } chnk_tbl_entry;
extern const chnk_tbl_entry chnk_type_name_sz_tbl[];

/*******************************************************
PROCEDURES
*******************************************************/
void decode_png_buf
    (
    decoder_ctx * ctx
    );

chnk_type_t8 get_chnk_from_type
    (
    char * name
    );

/* TODO: Move these functions to a more fitting file */
void store_bytes_int
    (
    uint8 * buf,
    uint8 * data,
    int sz
    );

void store_bytes
    (
    uint8 * buf,
    uint8 * data,
    int sz
    );

#endif /* PNG_DECODER_DECODE_PNG_H */

