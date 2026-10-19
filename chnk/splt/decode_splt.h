/***************************************************************
 * File: decode_splt.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_SPLT_H
#define PNG_DECODER_DECODE_SPLT_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

uint32 decode_splt_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

#endif /* PNG_DECODER_DECODE_SPLT_H */
