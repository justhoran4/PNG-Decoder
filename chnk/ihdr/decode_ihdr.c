/***************************************************************
 * File: decode_ihdr.c
 * Purpose: Decodes the IHDR chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

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
int i;

/*******************************************************
Initialize variables
*******************************************************/
i = 0;

for( int i = 0; i < 13; i++ )
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


return( i );
    
}
