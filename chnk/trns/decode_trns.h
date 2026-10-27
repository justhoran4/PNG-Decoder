/***************************************************************
 * File: decode_trns.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_TRNS_H
#define PNG_DECODER_DECODE_TRNS_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define TRNS_CHNK_SZ ( 0 )

uint32 decode_trns_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_trns_chnk
	(
	decoder_trns_chnk chnk
	);

png_decode_err_type validate_trns_chnk_dat_len
	(
	decoder_ctx * ctx
	);

#endif /* PNG_DECODER_DECODE_TRNS_H */
