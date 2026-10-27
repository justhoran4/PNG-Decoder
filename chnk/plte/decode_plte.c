/***************************************************************
 * File: decode_plte.c
 * Purpose: Decodes the PLTE chunk in a PNG file
 ***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "png_err_types.h"
#include "decode_plte.h"

/***************************************
FUNCTION:
    decode_plte_chnk

DESCRIPTION:
    Decodes the PLTE chunk in a PNG file. Returns the number of
    bytes stored for caller to validate.
***************************************/
uint32 decode_plte_chnk
    (
    decoder_ctx   * ctx,
    uint8         * data
    )
{
/*******************************************************
Local variables
*******************************************************/
uint32      bytes_read; /* total bytes read         */
uint32      sz;         /* size to read             */

/*******************************************************
Initialize variables
*******************************************************/
bytes_read = 0;
sz = ctx->chnk_lst->hdr.length;

ctx->chnk_lst->chnk.plte.plt_data = (uint8 *)malloc( sz );
memcpy( ctx->chnk_lst->chnk.plte.plt_data, data, sz  );
bytes_read = sz;

return( bytes_read );
    
}

/***************************************
FUNCTION:
    validate_plte_chnk

DESCRIPTION:
    Validates data within the PLTE chunk.
***************************************/
png_decode_err_type validate_plte_chnk
    (
    decoder_plte_chnk plte
    )
{
(void) plte;

return( ERR_PNG_DECODE_NONE );

}


/***************************************
FUNCTION:
    validate_plte_chnk_dat_len

DESCRIPTION:
    Validates the PLTE chunk data length.
    Assumes that the current chunk in
    the context chnk_lst is a PLTE chunk
***************************************/
png_decode_err_type validate_plte_chnk_dat_len
    (
    decoder_ctx * ctx
    )
{
/*******************************************************
Local variables
*******************************************************/
png_decode_err_type err;    /* return error         */

/*******************************************************
Initialize variables
*******************************************************/
err = ERR_PNG_DECODE_NONE;

if( ctx->chnk_lst->hdr.length != 0
|| ( ( ctx->chnk_lst->hdr.length % PLTE_ENT_SZ ) != 0 )
|| ( ctx->chnk_lst->hdr.length / PLTE_ENT_SZ ) > 256 )
    {
    return( ERR_PNG_DECODE_PLTE_SZ_WRONG );
    }

return( err );

}
