#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include  <zconf.h>


static struct option long_options[] =
{
	{"c", optional_argument, NULL, 'c'}, //Connecct
	{"a", optional_argument, NULL, 'a'}, //Accept
	{"i", optional_argument, NULL, 'i'}, //address
	{"p", optional_argument, NULL, 'p'},  //Port
	{"help", optional_argument, NULL, 'h'},
	{NULL, 0, NULL, 0}
};

extern int errno;
extern int optind, opterr, optopt;

void printhelp();


int main( int argc, char * argv[])
{
	//TODO
	int ch 	     = 0;
	int indexptr = 0;
	char state	= 0;

	while(  (ch = getopt_long( argc, argv, "c::a::i:p:", long_options, &indexptr)) != -1)
	{
		switch( ch)
		{
			case 'c':
				state = 2;
				printf("scanned Connection option\n");
				break;
			case 'a':
				state = 2;
				printf("scanned Accept option\n");
				break;
			case 'i':
				if( state != 2{
				}
				state = 3;
				printf("scanned address :  %s\n", optarg);
				break;
			case 'p':
					
				printf("scanned optional port\n");
				break;
			case 'h':
				printhelp();
				break;
			default:
				fprintf(stderr, "invalid option: -%c\n", opterr);
				return -1;
		}
	}
}// End Main

void printhelp(){
	printf("help menu\n");
}

