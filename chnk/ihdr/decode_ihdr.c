/***************************************************************
 * File: decode_ihdr.c
 * Purpose: Decodes the IHDR chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "png_err_types.h"
#include "decode_ihdr.h"

/***************************************
FUNCTION:
    decode_ihdr_chnk

DESCRIPTION:
    Decodes the IHDR chunk. Returns the
    number of bytes stored for caller to
    validate
***************************************/
uint32 decode_ihdr_chnk
    (
    decoder_ctx   * ctx,
    uint8         * data
    )
{
/*******************************************************
Local variables
*******************************************************/
uint32      i;              /* iterator                     */
uint32      bytes_read;     /* total bytes read             */

/*******************************************************
Initialize variables
*******************************************************/
i = 0;

for( int i = 0; i < IHDR_SZ; i++ )
    {
    printf( "%d ", data[ i ] );
    }

store_bytes_int( &data[ i ], (uint8 *) &ctx->chnk_lst->chnk.ihdr.width, sizeof( ctx->chnk_lst->chnk.ihdr.width ) );
i += sizeof( ctx->chnk_lst->chnk.ihdr.width );

store_bytes_int( &data[ i ], (uint8 *) &ctx->chnk_lst->chnk.ihdr.height, sizeof( ctx->chnk_lst->chnk.ihdr.height ) );
i += sizeof( ctx->chnk_lst->chnk.ihdr.height );

store_bytes_int( &data[ i ], (uint8 *) &ctx->chnk_lst->chnk.ihdr.bit_depth, sizeof( ctx->chnk_lst->chnk.ihdr.bit_depth ) );
i += sizeof( ctx->chnk_lst->chnk.ihdr.bit_depth );

store_bytes_int( &data[ i ], (uint8 *) &ctx->chnk_lst->chnk.ihdr.color_type, sizeof( ctx->chnk_lst->chnk.ihdr.color_type ) );
i += sizeof( ctx->chnk_lst->chnk.ihdr.color_type );

store_bytes_int( &data[ i ], (uint8 *) &ctx->chnk_lst->chnk.ihdr.compression_method, sizeof( ctx->chnk_lst->chnk.ihdr.compression_method ) );
i += sizeof( ctx->chnk_lst->chnk.ihdr.compression_method );

store_bytes_int( &data[ i ], (uint8 *) &ctx->chnk_lst->chnk.ihdr.filter_method, sizeof( ctx->chnk_lst->chnk.ihdr.filter_method ) );
i += sizeof( ctx->chnk_lst->chnk.ihdr.filter_method );

store_bytes_int( &data[ i ], (uint8 *) &ctx->chnk_lst->chnk.ihdr.interlace_method, sizeof( ctx->chnk_lst->chnk.ihdr.interlace_method ) );
i += sizeof( ctx->chnk_lst->chnk.ihdr.interlace_method );

printf( "IHDR values:\n" );
printf( "  Width: %u\n", ctx->chnk_lst->chnk.ihdr.width );
printf( "  Height: %u\n", ctx->chnk_lst->chnk.ihdr.height );
printf( "  Bit depth: %u\n", ctx->chnk_lst->chnk.ihdr.bit_depth );
printf( "  Color type: %u\n", ctx->chnk_lst->chnk.ihdr.color_type );
printf( "  Compression method: %u\n", ctx->chnk_lst->chnk.ihdr.compression_method );
printf( "  Filter method: %u\n", ctx->chnk_lst->chnk.ihdr.filter_method );
printf( "  Interlace method: %u\n", ctx->chnk_lst->chnk.ihdr.interlace_method );

bytes_read = i;

return( bytes_read );
    
}


/***************************************
FUNCTION:
    validate_ihdr_chnk

DESCRIPTION:
    Validates data within the IHDR chunk.
    The function assumes the ihdr chunk
    passed has been correctly decoded and
    stored in ihdr.
***************************************/
png_decode_err_type validate_ihdr_chnk
    (
    decoder_ihdr_chnk ihdr
    )
{
/*******************************************************
Local constants
*******************************************************/
uint8   bit_dpth_tbl[] = 
    {
    ( 1 << IHDR_BIT_DEPTH_1 ),
    ( 1 << IHDR_BIT_DEPTH_2 ),
    ( 1 << IHDR_BIT_DEPTH_3 ),
    ( 1 << IHDR_BIT_DEPTH_4 ),
    ( 1 << IHDR_BIT_DEPTH_5 ),
    };

/*******************************************************
Local variables
*******************************************************/
ihdr_bit_depth      bit_dpth;
png_decode_err_type err;

/*******************************************************
Initialize variables
*******************************************************/
bit_dpth = ihdr.bit_depth;
err = ERR_PNG_DECODE_NONE;

/*******************************************************
Heights and widths of 0 are invalid
*******************************************************/
if( ihdr.width == 0 || ihdr.height == 0 )
    {
    return( ERR_PNG_DECODE_IHDR_HGHT_WDTH );
    }

/*******************************************************
Heights and widths have a maximum size of
( ( 2^31 ) - 1 )
*******************************************************/
if( ihdr.width >= IHDR_MAX_DIMENSION_SZ || ihdr.height >= IHDR_MAX_DIMENSION_SZ )
    {
    return( ERR_PNG_DECODE_IHDR_HGHT_WDTH );
    }

/*******************************************************
Check for color type and respective bit depths
*******************************************************/
switch( ihdr.color_type )
    {
    case( IHDR_COLOR_TYPE_GRYSCL ):
        if( bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_1 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_2 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_3 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_4 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_5 ] )
            {
            return( ERR_PNG_DECODE_IHDR_INV_BIT_DPTH );
            }
        break;
    case( IHDR_COLOR_TYPE_RGB_TRPL ):
        if( bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_4 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_5 ] )
            {
            return( ERR_PNG_DECODE_IHDR_INV_BIT_DPTH );
            }
        break;
    case( IHDR_COLOR_TYPE_PLTE_IDX ):
        if( bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_1 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_2 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_3 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_4 ] )
            {
            return( ERR_PNG_DECODE_IHDR_INV_BIT_DPTH );
            }
        break;
    case( IHDR_COLOR_TYPE_GRYSCL_ALPH ):
        if( bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_4 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_5 ] )
            {
            return( ERR_PNG_DECODE_IHDR_INV_BIT_DPTH );
            }
        break;
    case( IHDR_COLOR_TYPE_RGB_TRPL_ALPH ):
        if( bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_4 ]
         && bit_dpth != bit_dpth_tbl[ IHDR_BIT_DEPTH_5 ] )
            {
            return( ERR_PNG_DECODE_IHDR_INV_BIT_DPTH );
            }
        break;
    /***************************************************
    Invalid color type
    ***************************************************/
    default:
        return( ERR_PNG_DECODE_IHDR_INV_COLOR_TYPE );
    }

/*******************************************************
Check that compresison method is 0, only valid method
currently
*******************************************************/
if( ihdr.compression_method != 0 )
    {
    return( ERR_PNG_DECODE_IHDR_INV_CMPRS_MTHD );
    }

/*******************************************************
Check that filter method is 0, only valid method
currently
*******************************************************/
if( ihdr.filter_method != 0 )
    {
    return( ERR_PNG_DECODE_IHDR_INV_FLTR_MTHD );
    }

/*******************************************************
Check that interlace method is one of two valid methods.
Either no interlace or the Adam7 interlace.
*******************************************************/
if( ihdr.interlace_method >= IHDR_INTLC_MTHD_CNT )
    {
    return( ERR_PNG_DECODE_IHDR_INV_INTLC_MTHD );
    }

return( err );

}


/***************************************
FUNCTION:
    validate_ihdr_chnk_dat_len

DESCRIPTION:
    Validates the data length of the
    IHDR chunk.
***************************************/
png_decode_err_type validate_ihdr_chnk_dat_len
	(
	decoder_ctx * ctx	
	)
{
/*******************************************************
Local variables
*******************************************************/
png_decode_err_type err;

/*******************************************************
Initialize variables
*******************************************************/
err = ERR_PNG_DECODE_NONE;

if( ctx->chnk_lst->hdr.length != IHDR_SZ )
    {
    err = ERR_PNG_DECODE_IHDR_SZ_WRONG;
    return( err );
    }

return( err );

}
