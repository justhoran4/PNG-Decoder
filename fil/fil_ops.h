#ifndef PNG_DECODER_FIL_OPS_H
#define PNG_DECODER_FIL_OPS_H

#include <stdio.h>

/*******************************************************
TYPES
*******************************************************/
typedef unsigned char boolean;

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#include "png_err_types.h"

typedef uint64 uptr;

/*******************************************************
CONSTANTS
*******************************************************/
#define TRUE    ( 1 )
#define FALSE   ( 0 )

size_t get_file_size( FILE *fp );

#endif /* PNG_DECODER_FIL_OPS_H */