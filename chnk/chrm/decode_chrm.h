/***************************************************************
 * File: decode_chrm.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_CHRM_H
#define PNG_DECODER_DECODE_CHRM_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define CHRM_CHNK_SZ ( 0 )

uint32 decode_chrm_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_chrm_chnk
	(
	decoder_chrm_chnk chnk
	);

png_decode_err_type validate_chrm_chnk_dat_len
	(
	decoder_ctx * ctx
	);

#endif /* PNG_DECODER_DECODE_CHRM_H */
