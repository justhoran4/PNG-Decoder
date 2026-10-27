/***************************************************************
 * File: decode_text.c
 * Purpose: Decodes the TEXT chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "decode_text.h"

/***************************************
FUNCTION:
    decode_text_chnk

DESCRIPTION:
    Decodes the TEXT chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_text_chnk
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
    validate_text_chnk

DESCRIPTION:
    Validates data within the TEXT chunk.
***************************************/
png_decode_err_type validate_text_chnk
    (
    decoder_text_chnk chnk
    )
{
(void) chnk;

return( ERR_PNG_DECODE_NONE );

}

/***************************************
FUNCTION:
    validate_text_chnk_dat_len

DESCRIPTION:
    Validates the data length of the TEXT chunk.
***************************************/
png_decode_err_type validate_text_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
if( TEXT_CHNK_SZ != 0
&& ctx->chnk_lst->hdr.length != TEXT_CHNK_SZ )
    {
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( ERR_PNG_DECODE_NONE );

}
