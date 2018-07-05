
#include "network.h"


#include "data.h"
#include "util.h"
#include "codes.h"


#include "bsd_sock.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int  n_close(int * fd)
{
	return s_close( fd );

}


char* n_getip(void* name)
{
	return s_getaddr( name );
}


int* n_sock( void *conn, char flag, char accept_opt, char* if_name)
{
	return s_sock(conn, flag, accept_opt, if_name);	
}	

