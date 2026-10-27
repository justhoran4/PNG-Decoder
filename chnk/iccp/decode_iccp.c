/***************************************************************
 * File: decode_iccp.c
 * Purpose: Decodes the ICCP chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "decode_iccp.h"

/***************************************
FUNCTION:
    decode_iccp_chnk

DESCRIPTION:
    Decodes the ICCP chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_iccp_chnk
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
    validate_iccp_chnk

DESCRIPTION:
    Validates data within the ICCP chunk.
***************************************/
png_decode_err_type validate_iccp_chnk
    (
    decoder_iccp_chnk chnk
    )
{
(void) chnk;

return( ERR_PNG_DECODE_NONE );

}

/***************************************
FUNCTION:
    validate_iccp_chnk_dat_len

DESCRIPTION:
    Validates the data length of the ICCP chunk.
***************************************/
png_decode_err_type validate_iccp_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
if( ICCP_CHNK_SZ != 0
&& ctx->chnk_lst->hdr.length != ICCP_CHNK_SZ )
    {
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( ERR_PNG_DECODE_NONE );

}
