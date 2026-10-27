/***************************************************************
 * File: decode_bkgd.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_BKGD_H
#define PNG_DECODER_DECODE_BKGD_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define BKGD_CHNK_SZ ( 0 )

uint32 decode_bkgd_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_bkgd_chnk
	(
	decoder_bkgd_chnk chnk
	);

png_decode_err_type validate_bkgd_chnk_dat_len
	(
	decoder_ctx * ctx
	);

#endif /* PNG_DECODER_DECODE_BKGD_H */
