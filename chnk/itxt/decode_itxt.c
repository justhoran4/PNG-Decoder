/***************************************************************
 * File: decode_itxt.c
 * Purpose: Decodes the ITXT chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "decode_itxt.h"

/***************************************
FUNCTION:
    decode_itxt_chnk

DESCRIPTION:
    Decodes the ITXT chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_itxt_chnk
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
    validate_itxt_chnk

DESCRIPTION:
    Validates data within the ITXT chunk.
***************************************/
png_decode_err_type validate_itxt_chnk
    (
    decoder_itxt_chnk chnk
    )
{
(void) chnk;

return( ERR_PNG_DECODE_NONE );

}

/***************************************
FUNCTION:
    validate_itxt_chnk_dat_len

DESCRIPTION:
    Validates the data length of the ITXT chunk.
***************************************/
png_decode_err_type validate_itxt_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
if( ITXT_CHNK_SZ != 0
&& ctx->chnk_lst->hdr.length != ITXT_CHNK_SZ )
    {
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( ERR_PNG_DECODE_NONE );

}
