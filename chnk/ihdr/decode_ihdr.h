/***************************************************************
 * File: decode_ihdr.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_IHDR_H
#define PNG_DECODER_DECODE_IHDR_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define IHDR_SZ     ( 13 )
#define IHDR_MAX_DIMENSION_SZ ( 0x80000000 )

typedef uint8 ihdr_color_types;
enum
    {
    IHDR_COLOR_TYPE_GRYSCL          = 0,
    IHDR_COLOR_TYPE_RGB_TRPL        = 2,
    IHDR_COLOR_TYPE_PLTE_IDX        = 3,
    IHDR_COLOR_TYPE_GRYSCL_ALPH     = 4,
    IHDR_COLOR_TYPE_RGB_TRPL_ALPH   = 6
    };

typedef uint8 ihdr_bit_depth;
enum
    {
    /***************************************************
    Allowed for color types 0 and 3
    ***************************************************/
    IHDR_BIT_DEPTH_1 = 0,
    IHDR_BIT_DEPTH_2 = 1,
    IHDR_BIT_DEPTH_3 = 2,
    
    /***************************************************
    Allowed for all color types
    ***************************************************/
    IHDR_BIT_DEPTH_4 = 3,

    /***************************************************
    Allowed for all color types except for 3
    ***************************************************/
    IHDR_BIT_DEPTH_5 = 4
    };

typedef uint8 ihdr_intlc_mthd;
enum
    {
    IHDR_INTLC_MTHD_NO_INTLC,
    IHDR_INTLC_MTHD_ADAM7,
    IHDR_INTLC_MTHD_CNT
    };

uint32 decode_ihdr_chnk
    (
    decoder_ctx   * ctx,
    uint8         * data
    );

png_decode_err_type validate_ihdr_chnk
    (
    decoder_ihdr_chnk ihdr
    );

png_decode_err_type validate_ihdr_chnk_dat_len
	(
	decoder_ctx * ctx	
	);

#endif /* PNG_DECODER_DECODE_IHDR_H */
