/***************************************************************
 * File: decode_srgb.c
 * Purpose: Decodes the SRGB chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "decode_srgb.h"

/***************************************
FUNCTION:
    decode_srgb_chnk

DESCRIPTION:
    Decodes the SRGB chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_srgb_chnk
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

(void) ctx;
(void) data;

/* TODO: Parse chunk data and advance i for each consumed byte. */

return( i );
    
}

/***************************************
FUNCTION:
    validate_srgb_chnk

DESCRIPTION:
    Validates data within the SRGB chunk.
***************************************/
png_decode_err_type validate_srgb_chnk
    (
    decoder_srgb_chnk chnk
    )
{
(void) chnk;

return( ERR_PNG_DECODE_NONE );

}

/***************************************
FUNCTION:
    validate_srgb_chnk_dat_len

DESCRIPTION:
    Validates the data length of the SRGB chunk.
***************************************/
png_decode_err_type validate_srgb_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
if( SRGB_CHNK_SZ != 0
&& ctx->chnk_lst->hdr.length != SRGB_CHNK_SZ )
    {
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( ERR_PNG_DECODE_NONE );

}
