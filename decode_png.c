#include "png_err_types.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "decode_chnk.h"
#include "decode_png.h"

/*******************************************************
FORWARD DECLARATIONS
*******************************************************/
static void decode_chunk
    (
    decoder_ctx    * ctx
    );

static void decode_chunks
    (
    decoder_ctx    * ctx
    );

static boolean validate_png_sig
    (
    decoder_ctx    * ctx
    );

/*******************************************************
CONSTANTS
*******************************************************/
const struct chnk_tbl_entry chnk_type_name_sz_tbl[] =
    {
    { CHNK_TYPE_IHDR, IHDR_CHNK_TYPE, sizeof( decoder_ihdr_chnk ), total_chnk_size( decoder_ihdr_chnk ) },
    { CHNK_TYPE_PLTE, PLTE_CHNK_TYPE, sizeof( decoder_plte_chnk ), total_chnk_size( decoder_plte_chnk ) },
    { CHNK_TYPE_IDAT, IDAT_CHNK_TYPE, sizeof( decoder_idat_chnk ), total_chnk_size( decoder_idat_chnk ) },
    { CHNK_TYPE_IEND, IEND_CHNK_TYPE, sizeof( decoder_iend_chnk ), total_chnk_size( decoder_iend_chnk ) },
    { CHNK_TYPE_CHRM, CHRM_CHNK_TYPE, sizeof( decoder_chrm_chnk ), total_chnk_size( decoder_chrm_chnk ) },
    { CHNK_TYPE_GAMA, GAMA_CHNK_TYPE, sizeof( decoder_gama_chnk ), total_chnk_size( decoder_gama_chnk ) },
    { CHNK_TYPE_ICCP, ICCP_CHNK_TYPE, sizeof( decoder_iccp_chnk ), total_chnk_size( decoder_iccp_chnk ) },
    { CHNK_TYPE_SBIT, SBIT_CHNK_TYPE, sizeof( decoder_sbit_chnk ), total_chnk_size( decoder_sbit_chnk ) },
    { CHNK_TYPE_SRGB, SRGB_CHNK_TYPE, sizeof( decoder_srgb_chnk ), total_chnk_size( decoder_srgb_chnk ) },
    { CHNK_TYPE_BKGD, BKGD_CHNK_TYPE, sizeof( decoder_bkgd_chnk ), total_chnk_size( decoder_bkgd_chnk ) },
    { CHNK_TYPE_HIST, HIST_CHNK_TYPE, sizeof( decoder_hist_chnk ), total_chnk_size( decoder_hist_chnk ) },
    { CHNK_TYPE_TRNS, TRNS_CHNK_TYPE, sizeof( decoder_trns_chnk ), total_chnk_size( decoder_trns_chnk ) },
    { CHNK_TYPE_PHYS, PHYS_CHNK_TYPE, sizeof( decoder_phys_chnk ), total_chnk_size( decoder_phys_chnk ) },
    { CHNK_TYPE_SPLT, SPLT_CHNK_TYPE, sizeof( decoder_splt_chnk ), total_chnk_size( decoder_splt_chnk ) },
    { CHNK_TYPE_TIME, TIME_CHNK_TYPE, sizeof( decoder_time_chnk ), total_chnk_size( decoder_time_chnk ) },
    { CHNK_TYPE_ITXT, ITXT_CHNK_TYPE, sizeof( decoder_itxt_chnk ), total_chnk_size( decoder_itxt_chnk ) },
    { CHNK_TYPE_TEXT, TEXT_CHNK_TYPE, sizeof( decoder_text_chnk ), total_chnk_size( decoder_text_chnk ) },
    { CHNK_TYPE_ZTXT, ZTXT_CHNK_TYPE, sizeof( decoder_ztxt_chnk ), total_chnk_size( decoder_ztxt_chnk ) }
    };

/***************************************
FUNCTION:
    decode_png_fil

DESCRIPTION:
    Decode a png file.
***************************************/
void decode_png_buf
    (
    decoder_ctx * ctx
    )
{

boolean is_valid_sig;

is_valid_sig = validate_png_sig( ctx );

if( !is_valid_sig )
    {
    printf( "Invalid PNG signature\n" );
    return; 
    }

decode_chunks( ctx );

}

/***************************************
FUNCTION:
    decode_chunk

DESCRIPTION:
    Decodes a specific PNG chunk.
***************************************/
static void decode_chunk
    (
    decoder_ctx   * ctx
    )
{
/*******************************************************
Local variables
*******************************************************/
uint32          data_len;
chnk_type_t8    chnk;
char            chunk_type[ CHNK_FLD_TYPE_SZ + 1 ]; /* Account for NULL terminator */
uint8         * chunk_data;
uint32          crc;

/*******************************************************
Initialization
*******************************************************/
data_len = 0;
chnk = CHNK_TYPE_INVALID;
memset( chunk_type, 0, sizeof( chunk_type ) );
chunk_data = NULL;
crc = 0;

/*******************************************************
Decode the length
*******************************************************/
store_bytes_int( &ctx->buf[ ctx->ofst ], (uint8 *) &data_len, CHNK_FLD_LEN_SZ );
ctx->ofst += CHNK_FLD_LEN_SZ;

/*******************************************************
Decode the chunk type
*******************************************************/
store_bytes( &ctx->buf[ ctx->ofst ], (uint8 *) chunk_type, CHNK_FLD_TYPE_SZ );
ctx->ofst += CHNK_FLD_TYPE_SZ;

/*******************************************************
Decode the data
*******************************************************/
chunk_data = (uint8 *)malloc( data_len * sizeof( uint8 ) );
store_bytes( &ctx->buf[ ctx->ofst ], chunk_data, data_len );
ctx->ofst += data_len;

/*******************************************************
Decode the CRC
*******************************************************/
store_bytes_int( &ctx->buf[ ctx->ofst ], (uint8 *) &crc, CHNK_FLD_CRC_SZ );
ctx->ofst += CHNK_FLD_CRC_SZ;

/*******************************************************
If the header data and actual data have been retrieved
then allocate the memory for the chunk
*******************************************************/
ctx->chnk_lst = (decoder_node_chnk *)malloc( sizeof( decoder_node_chnk ) );
memset( ctx->chnk_lst, 0, sizeof( *ctx->chnk_lst ) );
ctx->chnk_lst->hdr.length = data_len;
memcpy( ctx->chnk_lst->hdr.type, chunk_type, sizeof( ctx->chnk_lst->hdr.type ) );
ctx->chnk_lst->hdr.crc = crc;

printf("==============\n");
printf( "Current chunk length: %u\n", data_len );
printf( "Current chunk type: %s\n", chunk_type );
printf( "Current chunk CRC: %08x\n", crc );
printf( "Chunk List: %p\n", (void *)ctx->chnk_lst );
printf("==============\n");

// TODO CRC updates

// TODO call specific chunk type function
chnk = get_chnk_from_type( chunk_type );
decode_chnk_types( ctx, chnk, chunk_data );

/*******************************************************
Update chunk count after chunk has been successfully
stored
*******************************************************/
ctx->chnk_cnt += 1;

free( chunk_data );

}

/***************************************
FUNCTION:
    decode_chunks

DESCRIPTION:
    Parses the PNG chunks.
***************************************/
static void decode_chunks( decoder_ctx * ctx )
{
/*******************************************************
Local variables
*******************************************************/
decoder_node_chnk   * prev_chnk;

/*******************************************************
Initialize variables
*******************************************************/
prev_chnk = NULL;

if( ctx == NULL )
    {
    printf( "Invalid parser context!" );
    return;
    }

if( ctx->chnk_cnt > 0 && !(ctx->chnk_mask & get_chunk_mask( CHNK_TYPE_IHDR ) ) )
    {
    printf( "Parser context has been corrupted with no IHDR chunk" );
    return;
    }

/*******************************************************
Parse the IHDR Chunk and validate
*******************************************************/
decode_chunk( ctx );

if( get_chnk_from_type( (char *) ctx->chnk_lst->hdr.type ) != CHNK_TYPE_IHDR )
    {
    printf( "The first chunk is not the IHDR chunk. PNG file could have been corrupted!" );
    return;
    }

/*******************************************************
Make sure the IHDR chunk is set as the acting head of
the list of chunks.
*******************************************************/  
ctx->ihdr_chnk = ctx->chnk_lst; /* Set IHDR chunk as header of list             */

/*******************************************************
First iteration of list:
Set header chunk == current chunk
Set temp previous chunk to current chunk (head)
Move currrent chunk to next chunk
*******************************************************/  
prev_chnk = ctx->chnk_lst;      /* Set previous chunk to current chunk (IHDR)   */
ctx->chnk_lst = ctx->chnk_lst->next; /* Set current chunk to next chunk for modification */

while( ctx->iend == NULL && ctx->ofst < ctx->fil_len )
    {
    /*******************************************************
    Decode chunk and store in chunk pointed to by current
    chunk
    *******************************************************/  
    decode_chunk( ctx );

    /*******************************************************
    After chunk has been decoded, set current chunk's previous
    chunk to the temporary previous chunk
    Update the previous chunk to the current chunk
    Move the current chunk to the next chunk
    Repeat until all chunks decoded
    *******************************************************/  
    ctx->chnk_lst->prev = prev_chnk;
    prev_chnk = ctx->chnk_lst;
    ctx->chnk_lst = ctx->chnk_lst->next;
    }

// printf( "Current chunk length: %u\n", ctx->ihdr->hdr.length );
// printf( "Current chunk type: %s\n", ctx->ihdr->hdr.type );
// printf( "Current chunk CRC: %08x\n", ctx->ihdr->hdr.crc );

}


/***************************************
FUNCTION:
    get_chnk_from_type

DESCRIPTION:
    Gets chunk enum from chunk type that
    is in string format.
***************************************/
chnk_type_t8 get_chnk_from_type
    (
    char * name
    )
{
/*******************************************************
Local variables
*******************************************************/
int             i;
chnk_type_t8    ret;

/*******************************************************
Initialization
*******************************************************/
ret = CHNK_TYPE_INVALID;

for( i = 0; i < CHNK_TYPE_CNT; i++ )
    {
    if( strcmp( chnk_type_name_sz_tbl[ i ].chnk_name, name ) == 0 )
        {
        ret = chnk_type_name_sz_tbl[ i ].chnk_type;
        break;
        }
    }

return( ret );

}


/***************************************
FUNCTION:
    store_bytes_int

DESCRIPTION:
    Store bytes in an int.

TODO: Make the function return the
      number of bytes read
***************************************/
void store_bytes_int
    (
    uint8 * buf,
    uint8 * data,
    int sz
    )
{
/*******************************************************
Local variables
*******************************************************/
int i;

/*******************************************************
Bytes for int stored in big endian
*******************************************************/
for( i = 0; i < sz; i++ )
    {
    data[ (sz - 1) - i ] = buf[ i ];
    }

}


/***************************************
FUNCTION:
    store_bytes

DESCRIPTION:
    Store bytes in a str.
***************************************/
void store_bytes
    (
    uint8 * buf,
    uint8 * data,
    int sz
    )
{
/*******************************************************
Local variables
*******************************************************/
int i;

/*******************************************************
Bytes for int stored in order of left to right
*******************************************************/
for( i = 0; i < sz; i++)
    {
    data[ i ] = buf[ i ];
    }

}


/***************************************
FUNCTION:
    validate_png_sig

DESCRIPTION:
    Validates the PNG signature.
***************************************/
static boolean validate_png_sig( decoder_ctx * ctx )
{
/*******************************************************
Local variables
*******************************************************/
uint64 header;
int i;

/*******************************************************
Initialization
*******************************************************/
header = 0;

/*******************************************************
Go through header bytes and store them
*******************************************************/
for( i = 0; i < SIG_SZ; i++ )
    {
    header |= byte_shift_left( (uint64) ctx->buf[ i ], ( (SIG_SZ - 1) - i) );
    }

/*******************************************************
Validate the header and update the offset
*******************************************************/
if( header == PNG_SIGNATURE )
    {
    ctx->ofst = SIG_SZ;
    return TRUE;
    }

return FALSE;
} /* validate_png_sig()  */
