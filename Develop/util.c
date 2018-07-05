

#include "util.h"
#include "codes.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
* 	Remarks: 
*		Maintain a pool of allocation space pointers... for shutdown stuff
*
*/



void malloc_mempool(unsigned char malloc_size)
{
	unsigned char i 		= 0;
	
	/*security issue here */
	static void** mem_pool	= malloc(sizeof(void*)*malloc_size);

	if( !mem_pool )
	{
		perror("malloc_mempool allocation error");	
		goto:
			free_pool;	
	}
	
	static curr_size = 0;	
	static unsigned char pool_size = malloc_size;	

	while(i < pool_size)
	{
		mem_pool[i] =	0;
		i++;
	}

	free_pool:
		free(mem_pool);
}


void* u_malloc( size_t size)
{
	void *m = 0;	
	if( curr_size  < pool_size)
	{
		m = malloc(size);
		if( !m )
		{
			fprintf(stderr, "\nmemory exceeded\n");
			//actually, throw tuple away and return parsing
			free(m);	
			exit(1);
		}
		mem_pool[curr_size++] = m;
	}	
	
	return m;
}


/* Just a wrapper for consistency */
void u_free( void *p )
{
	free(p);
}

/* Free all allocated memory */
 void free_all()
{
	int i = 0;
	
	while( i < pool_size )
	{
		mem_pool[i++] = 0;
	}

	free(mem_pool);
}
