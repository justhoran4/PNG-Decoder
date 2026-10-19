#ifndef PNG_DECODER_DECODE_CHNK_H
#define PNG_DECODER_DECODE_CHNK_H

#include "png_err_types.h"
#include <stdio.h>
#include "decode_png.h"

void decode_chnk_types
    (
    decoder_ctx   * ctx,
    chnk_type_t8    chnk,
    uint8         * data
    );

#endif /* PNG_DECODER_DECODE_CHNK_H */