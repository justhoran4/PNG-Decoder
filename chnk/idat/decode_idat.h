/***************************************************************
 * File: decode_idat.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_IDAT_H
#define PNG_DECODER_DECODE_IDAT_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

#define IDAT_CHNK_SZ ( 0 )

uint32 decode_idat_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_idat_chnk
	(
	decoder_idat_chnk idat
	);

png_decode_err_type validate_idat_chnk_dat_len
	(
	decoder_ctx * ctx
	);

#endif /* PNG_DECODER_DECODE_IDAT_H */
