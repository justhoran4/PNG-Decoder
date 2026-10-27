/***************************************************************
 * File: decode_iend.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_IEND_H
#define PNG_DECODER_DECODE_IEND_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define IEND_CHNK_SZ ( 0 )

uint32 decode_iend_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_iend_chnk
	(
	decoder_iend_chnk chnk
	);

png_decode_err_type validate_iend_chnk_dat_len
	(
	decoder_ctx * ctx
	);

#endif /* PNG_DECODER_DECODE_IEND_H */
