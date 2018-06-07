
#include "data.h"
#include "util.h"
#include "codes.h"
#include "table.h"
#include "config.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>	

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>


extern int errno;


/* CONNECTION (Active) Table */
/* ACCEPT (Passive) Table */
CONN C_table[C_SIZE];
CONN A_table[A_SIZE]; //table of accepted connected addresses


/* Pointers to begining & end of C_table */
void *C_head;
void *C_tail;

/* Pointers to begining & end of A_table */
void *A_head;
void *A_tail;


int C_entries;
int A_entries;


/*dummy main.... used for testing table */
int main( int argc, char * argv[])
{
	//char name[32] = "www.google.com";
	char name[size_32] = "172.217.0.4";
	char name2[size_32] = "www.wwu.edu";
	table_init();	
	interface( CONNECT, name, sizeof(name), 9000);	
	interface( CONNECT, name2, sizeof(name2), 9000);	

	/*	
	if( 0 IS 0){ 
		printf("IS works\n");
	}
	if( 1 NOT 0)
		printf("NOT works\n");
	if( 1 AND 1)
		printf("AND works\n");
	*/	
	
	
}

int table_init(void)
{
	/* allocate all global */

	C_head 		= NULL;
	C_tail 		= NULL;	
	A_head 		= NULL;
	A_tail		= NULL;	
	C_entries	= 0;
	A_entries	= 0;
}


//TODO
/* Checks all parameters and generates CONN structure for insert() */
int interface( int type, char *name, int n_size, int port )
{
	int 	val			= 0;
	int 	indexptr 	= 0;	
	char 	remote_ip[size_256];
	
	struct 	in_addr ip;
	struct 	sockaddr_in *s_addr;
	struct 	addrinfo hints, *remote, *p;

	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family 	= AF_INET;
	hints.ai_socktype	= SOCK_STREAM;
	val 				= getaddrinfo( name, NULL, &hints, &remote);

	if( val NOT 0 )
	{
		fprintf(stderr, "\ninvalid dns name: %s\n", name);
		return -1;
	}
	
	for( p = remote; p != NULL; p = p->ai_next)
	{
		s_addr = (struct sockaddr_in *) p->ai_addr;
		strncpy( remote_ip, inet_ntoa( s_addr->sin_addr ), sizeof(remote_ip));
	}
	free(remote);

	CONN conn = (CONN) u_malloc(sizeof(*conn));
	conn->type = type;
	conn->port = port;
	strncpy( conn->name, name, sizeof(conn->name));
	strncpy( conn->address, remote_ip, sizeof(conn->address));
	printf("conn.type = %d\n", (int) conn->type);
	printf("conn.address = %s\n", conn->address);
	printf("conn.port = %d\n", conn->port);

	C_insert(conn);
	u_free(conn);
	return(EXIT_SUCCESS);
}// End Main



//TODO
int  C_insert( void *p){
	printf("insert\n");

	if( C_entries == C_SIZE )
	{
		fprintf(stderr, "Connection table size exceeded, connection tuple will be freed");	
	}
	
	CONN c = (CONN) p;	
	printf("conn.port = %d\n", c->port);
	if( C_head IS NULL )
	{
		C_head = &C_table[0];
		C_tail = C_head;
		printf("C_head set, location: %p\n", C_head);
		
		C_table[0] = c;
		C_tail = &C_table[1];	
	}
	else
	{
		C_tail=c;

		C_tail++;
		printf("New Conn added, location: %p\n", C_tail);

	}
	
	return SUCCESS;		
}


int  A_insert( void *p){
	printf("insert\n");
	CONN c = (CONN) p;	
	if( A_head IS NULL )
	{
		A_head = &A_table[0];
		A_tail = A_head;
		printf("C_head set, location: %p\n", A_head);
		
		A_table[0] = c;
		A_tail++;	
	}
	
	return SUCCESS;		
}


int delete( char* address)
{
	return SUCCESS;
}


int member( char *address ){
	return SUCCESS;
}
