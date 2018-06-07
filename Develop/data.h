#ifndef _DATA
#define _DATA

#include "config.h"

typedef enum {CONNECT=0, ACCEPT} TYPE;

typedef struct CONN_{
	TYPE type;
	char address [size_64];	
	char name [size_32];
	int port;
	int sd;
	int hash;	
	//struct addrinfo *addr_list;
} *CONN;

//typedef CONN_ *CONN;

#endif
