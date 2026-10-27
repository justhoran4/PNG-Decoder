/***************************************************************
 * File: decode_phys.c
 * Purpose: Decodes the PHYS chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "png_err_types.h"
#include "decode_phys.h"

/***************************************
FUNCTION:
    decode_phys_chnk

DESCRIPTION:
    Decodes the PHYS chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_phys_chnk
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
    validate_phys_chnk

DESCRIPTION:
    Validates data within the PHYS chunk.
    The function assumes the ihdr chunk
    passed has been correctly decoded and
    stored in ihdr.
***************************************/
png_decode_err_type validate_phys_chnk
    (
    decoder_phys_chnk phys
    )
{
/*******************************************************
Local variables
*******************************************************/
png_decode_err_type err;

/*******************************************************
Initialize variables
*******************************************************/
err = ERR_PNG_DECODE_NONE;

}


/***************************************
FUNCTION:
    validate_phys_chnk_dat_len

DESCRIPTION:
    Validates the data length of the
    PHYS chunk.
***************************************/
png_decode_err_type validate_phys_chnk_dat_len
	(
	decoder_ctx * ctx	
	)
{
/*******************************************************
Local variables
*******************************************************/
png_decode_err_type err;

/*******************************************************
Initialize variables
*******************************************************/
err = ERR_PNG_DECODE_NONE;

if( ctx->chnk_lst->hdr.length != PHYS_CHNK_SZ )
    {
    err = ERR_PNG_DECODE_PHYS_SZ_WRONG;
    }

return( err );

}
