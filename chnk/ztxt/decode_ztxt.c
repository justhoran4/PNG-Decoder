/***************************************************************
 * File: decode_ztxt.c
 * Purpose: Decodes the ZTXT chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "decode_ztxt.h"

/***************************************
FUNCTION:
    decode_ztxt_chnk

DESCRIPTION:
    Decodes the ZTXT chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_ztxt_chnk
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
    validate_ztxt_chnk

DESCRIPTION:
    Validates data within the ZTXT chunk.
***************************************/
png_decode_err_type validate_ztxt_chnk
    (
    decoder_ztxt_chnk chnk
    )
{
(void) chnk;

return( ERR_PNG_DECODE_NONE );

}

/***************************************
FUNCTION:
    validate_ztxt_chnk_dat_len

DESCRIPTION:
    Validates the data length of the ZTXT chunk.
***************************************/
png_decode_err_type validate_ztxt_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
if( ZTXT_CHNK_SZ != 0
&& ctx->chnk_lst->hdr.length != ZTXT_CHNK_SZ )
    {
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( ERR_PNG_DECODE_NONE );

}
