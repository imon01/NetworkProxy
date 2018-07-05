#ifndef _TABLE
#define _TABLE


#include "data.h"

/* make table, mem alloc */

/* maintain two pointer for conn stack, head and tai */



static RCODE C_insert( void* );
static RCODE A_insert( void* );
BOOL table_init(void);
RCODE t_lookup( char*, TYPE );
RCODE t_delete( char*, TYPE, int* );
RCODE interface( int, char *, char*, int );

#endif
