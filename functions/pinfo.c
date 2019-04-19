#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/stat.h>
#include "declarations.h"

void pinfo()
{
	fflush(stdout);
	char process[BUFSIZE];
	strcpy(process,"/proc/");
	int pid,virtual_mem;
	char pr_stat,pr_name[75];
	char exe[BUFSIZE],rel[BUFSIZE];

	if(args[1] == NULL)
	{
		strcat(process,"self");
	}
	else
	{
		strcat(process,args[1]);
	}

	char proc_stat[BUFSIZE];
	
	strcpy(proc_stat,process);
	strcat(proc_stat,"/stat");

	FILE * status = fopen(proc_stat,"r");
	if(status == NULL)
	{
		printf("Error: Cannot open file %s\n",proc_stat);
		return;
	}
	else
	{
		
		fscanf(status,"%d %s %c",&pid,pr_name,&pr_stat);
		printf("Pid -- %d\n",pid);
		printf("Process Status -- %c\n",pr_stat);
		fclose(status);

	}
	strcpy(proc_stat,process);
	strcat(proc_stat,"/statm");

	FILE * memory = fopen(proc_stat,"r");

	if(memory == NULL)
	{
		printf("Error: Cannot open file %s\n",proc_stat);
		return;
	}
	else
	{
		fscanf(memory,"%d",&virtual_mem);
		printf("Virtual Memory -- %d\n",virtual_mem);
		fclose(memory);
	}

	strcpy(proc_stat,process);
	strcat(proc_stat,"/exe");

	//strcpy(rel,"\0");
	//strcpy(exe,"\0");
	for (int l=0;l<BUFSIZE;l++)
	{
		rel[l] = '\0';
		exe[l] = '\0';
	}

	int check = readlink(proc_stat,exe,sizeof(exe));
	
	if(check < 0)
	{
		printf("Error: Cannot open file %s\n",proc_stat);
		return;
	}
	else
	{
		int j = 0,k;

		while(home[j] == exe[j] && j<home_len && j<strlen(exe))
		{
			j++;
		}

		int len=0;
		if(j==home_len)
		{
			rel[len++] = '~';
			for (k=j;k<strlen(exe);k++)
			{
				rel[len++] = exe[k];
			}
		}
		else
		{
			strcpy(rel,exe);
		}
		printf("Executable Path -- %s\n",rel);
		//printf("%s\n",home);
		//printf("%s\n",exe);
	}
}