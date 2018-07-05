#ifndef _UTIL
#define _UTIL

#define NOT !=
#define IS  ==
#define B_AND &
#define AND &&


void malloc_mempool(unsigned char);
void* u_malloc(int size);
void u_free( void *p);
void u_freeall();
#endif
