/***************************************************************
 * File: decode_plte.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_PLTE_H
#define PNG_DECODER_DECODE_PLTE_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define PLTE_ENT_SZ    ( 3 )   /* pallete entry size */

uint32 decode_plte_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_plte_chnk_dat_len
	(
	decoder_ctx * ctx	
	);

#endif /* PNG_DECODER_DECODE_PLTE_H */
