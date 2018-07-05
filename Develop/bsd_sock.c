
#include "data.h"
#include "util.h"
#include "codes.h"
#include "config.h"
#include "bsd_sock.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*A wrapper for socket close, for sake of consistency */
int s_close( int* sd )
{
	int value = FAILURE;
	if( close( (int)*sd ) NOT 0)
	{
		perror("close");
	}
	
	return (!value);	
	
}

char* s_getaddr(char *name)
{
	int val = 0;
	int index = 0;
	struct in_addr addr;
	struct sockaddr_in *s_addr;
	struct addrinfo hints, *remote, *p;
	
	char remote_addr[256];
	
	memset(&remote, 0, sizeof( remote ));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	val = getaddrinfo(name, NULL, &hints, &remote);

	if( val NOT 0 )
	{
		fprintf(stderr, "\ninvalid dns name: %s\n", name );
		return NULL;
	}
	 
	for( p = remote; p!= NULL; p = p->ai_next)
	{
		s_addr = ( struct sockaddr_in * ) p->ai_addr;
		strncpy( remote_addr, inet_ntoa( s_addr->sin_addr), sizeof( remote_addr ) );
	}

	freeaddrinfo( remote );	
	//u_free( remote );
	
	return remote_addr;
}


int* s_sock( void *p, char flag, char accept_opt, char* if_name)
{
	int sd = FAILURE;
	size_t n  = 0;
	char *addr;	
	CONN c = (CONN) p;
	struct sockaddr_in sock;
	
	n = sizeof( struct sockaddr_in ) ;
	
	sock.sin_family = AF_INET;
		
		
	if( c->type IS CONNECT)
	{
		/*
		*addr = get_addr(c->name);	
	
		if( name IS NULL )
		{
			return FAILURE;
		}
		*/	

		//strncpy( c->address, addr, sizeof(c->addr) );
		sock.sin_port = htons( (u_short) c->port);
		memcpy( sock.sin_addr.s_addr, c->address, sizeof(c->address));
		
		sd = socket( AF_INET, SOCK_STREAM, PF_INET );
		
		if( sd <  0 )
		{
			perror("socket");
			return FAILURE;
		}
		
		if( connect( sd, (struct sockaddr *) &sock, sizeof( sock) ) < 0 )
		{
			perror("connect");
			shutdown(sd, 2);
			return FAILURE;
		}
	}
	else
	{
		//something cool: optional listen on all network interfaces
		
		sock.sin_addr.s_addr = INADDR_ANY;
		sock.sin_port 		= htons( (u_short) c->port);
		
		sd = socket( AF_INET, SOCK_STREAM, 0);
		
		if( sd < 0 )
		{
			perror("socket");
			return FAILURE;
		}
		
		if( setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int) ) IS -1 )
		{
			perror("setsockopt");
			return FAILURE;
		}

		if( fcntl( sd, F_SETFL, O_NONBLOCK ) < 0)
		{
			perror("fcntl");
			return FAILURE;	
		} 
		
		if( listen( sd, n_accept )  < 0 )
		{
			perror("listen");
			shutdown( sd, 2 );
			return FAILURE;
		}
	}	
	//set CONN tuple descriptor	
	c->sd = sd;		
	return sd;
}
