/***************************************************************
 * File: decode_idat.c
 * Purpose: Decodes the IDAT chunk in a PNG file
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "png_err_types.h"
#include "decode_idat.h"

/*******************************************************
FUNCTION:
    decode_idat_chnk

DESCRIPTION:
    Decodes the IDAT chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
*******************************************************/
uint32 decode_idat_chnk
    (
    decoder_ctx   * ctx,
    uint8         * data
    )
{
/*******************************************************
Local variables
*******************************************************/
int                 bytes_read;
uint32              sz;

/*******************************************************
Initialize variables
*******************************************************/
bytes_read = 0;
sz = 0;

/*******************************************************
Ensure the right chunk is being read
*******************************************************/
if( get_chnk_from_type( ctx->chnk_lst->hdr.type ) != CHNK_TYPE_IDAT )
    {
    return( 0 );
    }

sz = ctx->chnk_lst->hdr.length;

if( !( ctx->chnk_lst->chnk.idat.data = (uint8 *) malloc( sz ) ) )
    {
    return( 0 );
    }

if( !memcpy( ctx->chnk_lst->chnk.idat.data, data, sz ) )
    {
    return( 0 );
    }

bytes_read = sz;

return( bytes_read );
    
}
