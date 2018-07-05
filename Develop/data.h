#ifndef _DATA
#define _DATA



#include "config.h"

typedef enum {FALSE		=0	, TRUE} BOOL;
typedef enum {CONNECT	=0	, ACCEPT} TYPE;
typedef enum {FAILURE 	= -1, SUCCESS = 1} RCODE;

typedef struct CONN_{
	
	TYPE type;
	
	int sd;
	int hash;	
	int port;
	int group_id;	
	char name		[size_32];
	char address 	[size_64];	
	//struct addrinfo *addr_list;
} *CONN;

//typedef CONN_ *CONN;

#endif
