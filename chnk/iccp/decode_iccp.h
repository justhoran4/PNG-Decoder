/***************************************************************
 * File: decode_iccp.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_ICCP_H
#define PNG_DECODER_DECODE_ICCP_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

uint32 decode_iccp_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

#endif /* PNG_DECODER_DECODE_ICCP_H */
