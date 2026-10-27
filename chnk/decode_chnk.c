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
#include "decode_bkgd.h"
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
        /*******************************************************
        Make sure IDAT chunks are in consecutive order. If this
        is not the first IDAT chunk, this makes sure the
        previous chunk is an IDAT chunk or an error will be
        thrown
        *******************************************************/
        if( ( ctx->chnk_mask & get_chunk_mask( CHNK_TYPE_IDAT ) ) && get_chnk_from_type( ctx->chnk_lst->prev->hdr.type ) != CHNK_TYPE_IDAT )
            {
            err = ERR_PNG_DECODE_IDAT_INV_SEQUENCE;
            return( err );
            }

        bytes_read = decode_idat_chnk( ctx, data );

        break;
    case CHNK_TYPE_IEND:
        if( ( err = validate_iend_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        break;
    case CHNK_TYPE_CHRM:
        if( ( err = validate_chrm_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }
        
        break;
    case CHNK_TYPE_ICCP:
        if( ( err = validate_iccp_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }
        
        break;
    case CHNK_TYPE_SBIT:
        if( ( err = validate_sbit_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }
        
        break;
    case CHNK_TYPE_SRGB:
        if( ( err = validate_srgb_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }            

        break;
    case CHNK_TYPE_BKGD:
        if( ( err = validate_bkgd_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }
        
        break;
    case CHNK_TYPE_HIST:
        if( ( err = validate_hist_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }
        
        break;
    case CHNK_TYPE_TRNS:
        if( ( err = validate_trns_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }
        
        break;
    case CHNK_TYPE_PHYS:
        if( ( err = validate_phys_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }
        break;
    case CHNK_TYPE_SPLT:
        if( ( err = validate_splt_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        break;
    case CHNK_TYPE_TIME:
        if( ( err = validate_time_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        break;
    case CHNK_TYPE_ITXT:
        if( ( err = validate_itxt_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        break;
    case CHNK_TYPE_TEXT:
        if( ( err = validate_text_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        break;
    case CHNK_TYPE_ZTXT:
        if( ( err = validate_ztxt_chnk_dat_len( ctx ) ) )
            {
            return( err );
            }

        break;
    default:
        break;
    }

/*******************************************************
Validate the number of bytes read
*******************************************************/
if( bytes_read != ctx->chnk_lst->hdr.length )
    {
    printf( "Data size error for the %s chunk\n", chnk_type_name_sz_tbl[ chnk ].chnk_name );
    return( ERR_PNG_DECODE_CHUNK_DATA_SIZE );
    }

return( err );

} /* decode_chunk_types */