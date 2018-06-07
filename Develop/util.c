
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
* 	Remarks: 
*		Maintain a pool of allocation space pointers... for shutdown stuff
*
*/

void * u_malloc( int size)
{
	void *m = malloc(size);
	if( !m )
	{
		fprintf(stderr, "\nmemory exceeded\n");
		//actually, throw tuple away and return parsing
		exit(1);
	}

	return m;
}


/* Just a wrapper for consistency */
void u_free( void *p )
{
	free(p);
}
