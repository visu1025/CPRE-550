
#include "RSM1.h"
#include <stdio.h>
#include <string.h>

//this function is to make sure that the user gives only an integer input
long sanitizedInput()
{
	char input[100];
	int response;
	long option;
	while(1)
	{
		scanf("%s", input);
		if(input == NULL){
			printf("\nplease enter an option or press 7 to exit\n");
			continue;
		}
		if(sscanf(input, "%i", &response) == 1)		//search integer in the input string
		{	option = (long)response;
			return option;
		}
		else
			printf("\n Enter an integer\n");
	}
		
}			

//this function prompts user to give input.
long getResponse()
{	
	long response;
	printf("****MENU****\n");
	printf("1. ONLY DATE\n");
	printf("2. ONLY TIME\n");
	printf("3. DATE AND TIME\n");
	printf("4. Memory Usage\n");
	printf("5. Load procs per min \n");
	printf("6. CPU usage\n");
	printf("7. EXIT\n");
	printf("Please Enter your choice an integer between 1 -7 (inclusive):\n");
	response = sanitizedInput();
	return (response);
}


void
testprog1_1(char *host)
{
	CLIENT *clnt;
	char * *result_1;
	long  date_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, TESTPROG1, VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	label: date_1_arg = getResponse();
	//loop continues until the user enters quit option
	while (date_1_arg !=7)
	{
	result_1 = date_1(&date_1_arg, clnt);
	if (result_1 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	fprintf(stderr, "Generated Output: %s\n ", *result_1);
	date_1_arg = getResponse();
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	testprog1_1 (host);
exit (0);
}
