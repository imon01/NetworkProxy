#ifndef _TABLE
#define _TABLE

/* make table, mem alloc */

/* maintain two pointer for conn stack, head and tai */
int table_init(void);
int t_member( char* );
int C_insert( void* );
int A_insert( void* );
int t_delete( char* );

int interface( int, char *, int, int );
#endif
