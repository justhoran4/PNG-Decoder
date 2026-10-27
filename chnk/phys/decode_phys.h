/***************************************************************
 * File: decode_phys.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_PHYS_H
#define PNG_DECODER_DECODE_PHYS_H

#include "png_err_types.h"
#include <stdio.h>

#include "decode_png.h"

/*******************************************************
CONSTANTS
*******************************************************/
#define PHYS_CHNK_SZ	( 9 )

uint32 decode_phys_chnk
	(
	decoder_ctx   * ctx,
	uint8         * data
	);

png_decode_err_type validate_phys_chnk
    (
    decoder_phys_chnk ihdr
    );

png_decode_err_type validate_phys_chnk_dat_len
	(
	decoder_ctx * ctx	
	);

#endif /* PNG_DECODER_DECODE_PHYS_H */
