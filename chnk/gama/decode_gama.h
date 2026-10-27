/***************************************************************
 * File: decode_gama.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_GAMA_H
#define PNG_DECODER_DECODE_GAMA_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define GAMA_CHNK_SZ ( 0 )

uint32 decode_gama_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_gama_chnk
	(
	decoder_gama_chnk chnk
	);

png_decode_err_type validate_gama_chnk_dat_len
	(
	decoder_ctx * ctx
	);

#endif /* PNG_DECODER_DECODE_GAMA_H */
