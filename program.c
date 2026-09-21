#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fil_ops.h"
#include "decode_png.h"

#define PNG_FILE "png_samples\\ajou_logo.png"

int main
    (
    void
    )
{
/*******************************************************
Local variables
*******************************************************/
decoder_ctx ctx;
FILE *fp;

/*******************************************************
Initialization
*******************************************************/
memset( &ctx, 0, sizeof( ctx ) );
fp = fopen( PNG_FILE, "rb" );

if( fp == NULL )
    {
    printf( "Failed to open file: %s\n", PNG_FILE );
    return -1;
    }

ctx.fil_len = get_file_size( fp );

ctx.buf = (uint8 *)malloc( ctx.fil_len * sizeof( uint8 ) );
if( ctx.buf == NULL )
    {
    printf( "Failed to allocate memory for file buffer\n" );
    fclose( fp );
    return -1;
    }

printf( "File size: %zu bytes\n", ctx.fil_len  );
memset( ctx.buf, 0, ctx.fil_len );

fread( ctx.buf, 1, ctx.fil_len, fp );

// for ( size_t i = 0; i < 8; i++ )
//     {
//     printf( "%02x ", (uint8)buf[i] );
//     if ( (i + 1) % 16 == 0 )
//         {
//         printf( "\n" );
//         }
//     }

decode_png_buf( &ctx );

free( ctx.buf );
fclose( fp );

return 0;
}