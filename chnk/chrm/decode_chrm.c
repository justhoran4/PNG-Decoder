/***************************************************************
 * File: decode_chrm.c
 * Purpose: Decodes the CHRM chunk in a PNG file
 ***************************************************************/

#include <stdio.h>

#include "png_err_types.h"
#include "decode_chrm.h"

/***************************************
FUNCTION:
    decode_chrm_chnk

DESCRIPTION:
    Decodes the CHRM chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_chrm_chnk
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
