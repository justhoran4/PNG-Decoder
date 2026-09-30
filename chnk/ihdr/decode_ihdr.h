/***************************************************************
 * File: decode_ihdr.h
 * Purpose: Contains definitions of this chunk
 ***************************************************************/

#ifndef PNG_DECODER_DECODE_IHDR_H
#define PNG_DECODER_DECODE_IHDR_H

#include <stdio.h>

#include "decode_png.h"

uint32 decode_ihdr_chnk
    (
    decoder_ctx   * ctx,
    uint8         * data
    );

#endif /* PNG_DECODER_DECODE_IHDR_H */
