/***************************************************************
 * File: decode_sbit.c
 * Purpose: Decodes the SBIT chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "decode_sbit.h"

/***************************************
FUNCTION:
    decode_sbit_chnk

DESCRIPTION:
    Decodes the SBIT chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_sbit_chnk
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
    validate_sbit_chnk

DESCRIPTION:
    Validates data within the SBIT chunk.
***************************************/
png_decode_err_type validate_sbit_chnk
    (
    decoder_sbit_chnk chnk
    )
{
(void) chnk;

return( ERR_PNG_DECODE_NONE );

}

/***************************************
FUNCTION:
    validate_sbit_chnk_dat_len

DESCRIPTION:
    Validates the data length of the SBIT chunk.
***************************************/
png_decode_err_type validate_sbit_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
if( SBIT_CHNK_SZ != 0
&& ctx->chnk_lst->hdr.length != SBIT_CHNK_SZ )
    {
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( ERR_PNG_DECODE_NONE );

}
