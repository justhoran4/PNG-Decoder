/***************************************************************
 * File: decode_sbit.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_SBIT_H
#define PNG_DECODER_DECODE_SBIT_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define SBIT_CHNK_SZ ( 0 )

uint32 decode_sbit_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_sbit_chnk
	(
	decoder_sbit_chnk chnk
	);

png_decode_err_type validate_sbit_chnk_dat_len
	(
	decoder_ctx * ctx
	);

#endif /* PNG_DECODER_DECODE_SBIT_H */
