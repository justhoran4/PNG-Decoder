/* Module to handle the decoding of all of the chunks */

#include "png_err_types.h"

#include <stdio.h>
#include <string.h>

#include "decode_chnk.h"
#include "decode_ihdr.h"
#include "decode_plte.h"
#include "decode_idat.h"
#include "decode_iend.h"
#include "decode_chrm.h"
#include "decode_gama.h"
#include "decode_iccp.h"
#include "decode_sbit.h"
#include "decode_srgb.h"
#include "decode_hist.h"
#include "decode_trns.h"
#include "decode_phys.h"
#include "decode_splt.h"
#include "decode_time.h"
#include "decode_itxt.h"
#include "decode_text.h"
#include "decode_ztxt.h"

/***************************************
FUNCTION:
    decode_chunk_types

DESCRIPTION:
    This function handles the calls to
    decode each specific chunk.

    TODO: Maybe replace with callback
          functions in the chunk table
***************************************/
png_decode_err_type decode_chnk_types
    (
    decoder_ctx   * ctx,
    chnk_type_t8    chnk,
    uint8         * data
    )
{
/*******************************************************
Local variables
*******************************************************/
uint32              bytes_read;
png_decode_err_type err;

/*******************************************************
Initialize variables
*******************************************************/
bytes_read = 0;
err = ERR_PNG_DECODE_NONE;

switch( chnk )
    {
    case CHNK_TYPE_IHDR:
        if( ( err = validate_ihdr_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        bytes_read = decode_ihdr_chnk( ctx, data );

        err = validate_ihdr_chnk( ctx->chnk_lst->chnk.ihdr );

        if( err != ERR_PNG_DECODE_NONE )
            {
            return( err );
            }
        
        break;
    case CHNK_TYPE_PLTE:
        if( ( err = validate_plte_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        bytes_read = decode_plte_chnk( ctx, data );
        
        break;
    case CHNK_TYPE_IDAT:
        break;
    case CHNK_TYPE_IEND:
        break;
    case CHNK_TYPE_CHRM:
        break;
    case CHNK_TYPE_ICCP:
        break;
    case CHNK_TYPE_SBIT:
        break;
    case CHNK_TYPE_SRGB:
        break;
    case CHNK_TYPE_BKGD:
        break;
    case CHNK_TYPE_HIST:
        break;
    case CHNK_TYPE_TRNS:
        break;
    case CHNK_TYPE_PHYS:
        break;
    case CHNK_TYPE_SPLT:
        break;
    case CHNK_TYPE_TIME:
        break;
    case CHNK_TYPE_ITXT:
        break;
    case CHNK_TYPE_TEXT:
        break;
    case CHNK_TYPE_ZTXT:
        break;
    default:
        break;
    }

/*******************************************************
Validate the number of bytes read
*******************************************************/
if( bytes_read != chnk_type_name_sz_tbl[ chnk ].chnk_data_sz )
    {
    printf( "Data size error for the IHDR chunk\n" );
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( err );

} /* decode_chunk_types */