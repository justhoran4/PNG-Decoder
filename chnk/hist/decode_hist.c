/***************************************************************
 * File: decode_hist.c
 * Purpose: Decodes the HIST chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "decode_hist.h"

/***************************************
FUNCTION:
    decode_hist_chnk

DESCRIPTION:
    Decodes the HIST chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_hist_chnk
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
    validate_hist_chnk

DESCRIPTION:
    Validates data within the HIST chunk.
***************************************/
png_decode_err_type validate_hist_chnk
    (
    decoder_hist_chnk chnk
    )
{
(void) chnk;

return( ERR_PNG_DECODE_NONE );

}

/***************************************
FUNCTION:
    validate_hist_chnk_dat_len

DESCRIPTION:
    Validates the data length of the HIST chunk.
***************************************/
png_decode_err_type validate_hist_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
if( HIST_CHNK_SZ != 0
&& ctx->chnk_lst->hdr.length != HIST_CHNK_SZ )
    {
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( ERR_PNG_DECODE_NONE );

}
