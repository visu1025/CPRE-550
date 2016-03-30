/*
Author: Venkata Kasi Viswanath Yeleswarapu
Lanugage: Developed in C using RPC middleware
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>
#include <rpc/rpc.h>
#include "RSM1.h"

char **
date_1_svc(long *argp, struct svc_req *rqstp)
{
	static char * result;
	struct tm *info;
	static char output[100];
	FILE *fp;

	//functions from time.h header file
	time_t seconds;
	seconds = time(NULL);
	info = localtime(&seconds);
	
	//functions from sys/sysinfo.h header file
	struct sysinfo sysInfo;
        sysinfo(&sysInfo);

        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
	
	char cpuUsage[100];

	if(*argp > 7 || *argp < 0)
	{
		result = "Invalid Response\n";
		return &result;
	}
	switch(*argp){
	case 1:
		strftime(output, 100, "%A, %B %d, %Y", info);
		break;
	case 2:
		strftime(output, 100, "%T", info);
		break;
	case 3:
		strftime(output, 100, "%A, %B %d, %Y - %T", info);
		break;
	case 4:
                sprintf(output, "\nTotal RAM Available: %u \nFree RAM Available: %u \nRAM used up: %u \n",
                        sysInfo.totalram * (unsigned long) sysInfo.mem_unit /1024,
                        sysInfo.freeram * (unsigned long) sysInfo.mem_unit /1024,
                        sysInfo.totalram * (unsigned long) sysInfo.mem_unit /1024 - sysInfo.freeram * (unsigned long) sysInfo.mem_unit /1024);
		break;

	case 5:
                sprintf(output, "\nLoad procs per 1 min : %f \nLoad procs per 5 mins: %f\nLoad procs per 15 mins: %f \n", sysInfo.loads[0]/65536.0, sysInfo.loads[1]/65536.0, sysInfo.loads[2]/65536.0);
		break;
	case 6:
                fp = popen ("top -b -d1 -n1|grep -i '^Cpu.s.'|head -c24", "r");

                if(fp == NULL){
                fprintf(stderr, "Unable to open CPU Usage file");
                result = " Could not complete the request";
                }
				//set memory to O for cpuUsage field.
		memset(cpuUsage, 0, 100);
                fread(cpuUsage, 100*sizeof(char), 100, fp);
		sprintf(output, "\nCPU Usage is : %s\nHere us represents User CPU time and sy represents System CPU time\n", cpuUsage);
                break;

	default:
		result = " Invalid Response";
		break;
	}
	result = output;
	return &result;
}
