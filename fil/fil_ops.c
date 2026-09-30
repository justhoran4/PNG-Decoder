#include "fil_ops.h"

/***************************************
FUNCTION:
    get_file_size

DESCRIPTION:
    Returns the size of the file in
    bytes.
***************************************/
size_t get_file_size( FILE *fp )
{
size_t size;

if( fp == NULL )
{
return( (size_t) -1 );
}

fseek(fp, 0, SEEK_END);
size = ftell(fp);
fseek(fp, 0, SEEK_SET);
return size;
} /* get_file_size() */
