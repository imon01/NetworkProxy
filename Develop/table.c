/*

Table.c


Structures:
	Accept connection table
	Connect connection table

Features:
	insert
	delete
	lookup

Warnings:
	NO CONCURRENT SUPPORT


*/


/* Support system module(s) */
#include "data.h"
#include "util.h"
#include "codes.h"
#include "table.h"
#include "config.h"


/* Interacting system module(s) */
#include "network.h"



/* Other */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>	

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>



/* ************************************************************* */
/* 					Table variables								 */
/* ************************************************************* */



extern int errno;
static BOOL t_flag = FALSE;



CONN C_table[C_SIZE]; /* CONNECTION (Active) Table */
CONN A_table[A_SIZE]; /* ACCEPT (Passive) Table */


/* Pointers to begining & end of C_table */
void *C_head;
void *C_tail;

/* Pointers to begining & end of A_table */
void *A_head;
void *A_tail;

/* Number of table entries	*/
int C_entries;
int A_entries;




/* *************************************************************	*/
/* 					Local  Prototypes								*/
/* ************************************************************* 	*/



unsigned long hash(char*);




/* *************************************************************	*/
/* 					Table Procedures								*/
/* ************************************************************* 	*/



BOOL table_check()
{
	return t_flag;
}

BOOL table_init(void)
{
	if( t_flag )
	{	
		perror("table already created");
		return FALSE;
	}

	/* allocate all global */
	t_flag		= TRUE;
	C_head 		= NULL;
	C_tail 		= NULL;	
	A_head 		= NULL;
	A_tail		= NULL;	
	C_entries	= 0;
	A_entries	= 0;
	
	return TRUE;
}


//TODO
/* Checks all parameters and generates CONN structure for insert() */
RCODE interface( int type, char *name, char *address, int port )
{
	/*
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
	*/

	int insert_val = 0;	
	CONN conn = (CONN) u_malloc(sizeof(*conn));

	if( conn )
	{
		conn->type = type;
		conn->port = port;
		strncpy( conn->name, name, strlen(conn->name));
		strncpy( conn->address, address, strlen(conn->address));
		printf("conn.type = %d\n", (int) conn->type);
		printf("conn.address = %s\n", conn->address);
		printf("conn.port = %d\n", conn->port);

	}
	
	//C_insert(conn);
	//	u_free(conn);
	
	if( type IS CONNECT)
		insert_val = C_insert(conn);
	else
		insert_val = A_insert(conn);

	if( insert_val == FAILURE )
		u_free(conn);
	
	return insert_val;
}// End Main



//TODO
static RCODE  C_insert( void *p){
	printf("insert\n");

	if( C_entries == C_SIZE )
	{
		fprintf(stderr, "Connection table size exceeded, connection tuple will be freed");	
		return FAILURE;	
	}
	
	CONN c = (CONN) p;	
	//printf("conn.port = %d\n", c->port);
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


static RCODE  A_insert( void *p)
{

	if( A_entries == A_SIZE )
	{
		fprintf(stderr, "Accept table size exceeded, accept tuple will be freed");
		return FAILURE;
	}

	CONN c = (CONN) p;
	
	if( A_head IS NULL )
	{
		A_head = &A_table[0];
		A_tail = A_head;
		printf("C_head set, location: %p\n", A_head);
		
		A_table[0] = c;
		A_tail	= &C_table[1];	
	}
	else
	{
		A_tail = c;
		A_tail++;
		printf("New Conn added, location: %p\n", A_tail);
	}
	return SUCCESS;		
}


RCODE t_delete(char* address, TYPE type, int *sd)
{
	RCODE value = FALSE; 
	size_t 	addr_len = sizeof(address);

	if( !t_flag ) 
		return FAILURE;

	int	limit		= 0;
	int* actual		= 0;	
	CONN* table		 = 0;

	if(type IS CONNECT)
	{
		actual 		= &C_entries;	
		limit 		= C_entries;
		table 		= C_table;
	
	}
	else
	{
		actual 		= &A_entries;
		limit 		= A_entries;	 
		table	 	= A_table;
	}		
	


	for(int i = 0; i < limit; i++)
	{
		if( strncmp( table[i]->address, address, addr_len ) IS 0 )
		{
			i		= limit;		
			value 	= SUCCESS; 
			n_close( table[i]->sd );				
			u_free( table[i] );

			*actual = (*actual) - 1;	
			//must close socket descriptor	
		}
	}
	


	 
	return value;
}


RCODE t_lookup(char *address, TYPE type )
{
	size_t addr_len	= strlen(address);
	RCODE value 	= FAILURE;
	
	if( !t_flag )
	{ 
		return FAILURE;
	}

	int	limit		= 0;
	CONN* table		= 0;

	if(type IS CONNECT)
	{
		limit 		= C_entries;
		table 		= C_table;
	
	}
	else
	{
		limit 		= A_entries;	 
		table	 	= A_table;
	}		
	
	for(int i = 0; i < limit; i++)
	{
		if( strncmp( table[i]->address, address, addr_len ) IS 0 )
		{
			i		= limit;	
			value 	= SUCCESS; 
		}
	}
	
	return value; 
}




//dj2 from www.cse.yorku.ca/~oz/hash.html 
unsigned long  hash(char* address)
{
	int c				= 0;
	unsigned long hash 	= 5381;
	
	while( c = *address++ )
	{
		hash =  ( ( hash << 5 ) +  hash) + c; /* hash*33 + c */
	}

	return hash;


}


