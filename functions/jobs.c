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

void jobs(int to_print)
{
	int itr;
	fflush(stdout);
	char process[BUFSIZE];
	int pid,virtual_mem;
	char pr_stat,pr_name[75],proc_stat[BUFSIZE],str_pid[10];

	active = 0;

	for(itr = 0; itr < num_background_proc ;itr++)
	{
		if(back_proc[itr].state = 1)
		{
			strcpy(process,"/proc/");
			sprintf(str_pid, "%d", back_proc[itr].pid);
			strcat(process,str_pid);

			strcpy(proc_stat,process);
			strcat(proc_stat,"/stat");

			//printf("%s\n",proc_stat);
			FILE * status = fopen(proc_stat,"r");
			if(status == NULL)
			{
			//printf("Error: Cannot Read Status\n");
				//back_proc[itr].status = 'F';
				continue;
			}
			else
			{

				fscanf(status,"%d %s %c",&pid,pr_name,&back_proc[itr].status);
		//printf("Pid -- %d\n",pid);
		//printf("Process Status -- %c\n",pr_stat);
				fclose(status);
				
				job_proc[active].jobid = active;
				job_proc[active].pid = back_proc[itr].pid;
				job_proc[active].status = back_proc[itr].status;
				strcpy(job_proc[active].command, back_proc[itr].command);
				active++;
			}

		}
		strcpy(process,"\0");
	}

	if(to_print == 1)
	{
		if(active == 0)
		{
			printf("%s\n","No Active Processes");
		}
		else
		{
			for(itr=0;itr<active;itr++)
			{
				printf("[%d]\t",job_proc[itr].jobid);

				if(job_proc[itr].status == 'S')
				{
					printf("%s","Sleeping");
				}
				else if(job_proc[itr].status == 'T')
				{
					printf("%s","Stopped");
				}
				else if(job_proc[itr].status == 'R')
				{
					printf("%s","Running");
				}

				printf("\t\t%s [%d]\n",job_proc[itr].command,job_proc[itr].pid);
			}
		}
	}
	return;
}

void kjob()
{
	int itr;
	char t1[10], t2[10];

	if(args[1]==NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: kjob <jobid> <signal>\n");
		return;

	}

	if(args[1] != NULL)
		strcpy(t1,args[1]);
	if(args[2] != NULL)	
		strcpy(t2,args[2]);


	//printf("%s %s\n", args[1], args[2]);
	jobs(0);
	//printf("%s %s\n", args[1], args[2]);
	int jobid = atoi(t1);

	if(jobid >= active)
	{
		fprintf(stderr, "Job Does Not Exist\n");
		return;
	}

	int signal=atoi(t2);

	//printf("%s %s\n", args[1], args[2]);

	//printf("%d %d\n", jobid, signal);

	//printf("%d %d\n", job_proc[jobid].pid,signal);
	kill(job_proc[jobid].pid,signal);

	if(signal == 9)
	{
		for(itr = 0; itr<num_background_proc;itr++)
		{
			if(back_proc[itr].pid == job_proc[jobid].pid)
			{
				back_proc[itr].state = -1;
			}
		}
	}
	else if(signal == 18)
	{
		for(itr = 0; itr<num_background_proc;itr++)
		{
			if(back_proc[itr].pid == job_proc[jobid].pid)
			{
				back_proc[itr].state = 1;
			}
		}
	}
}

void fg()
{
	char t1[10];
	int itr,status;
	
	if(args[1] == NULL)
	{
		fprintf(stderr, "Usage: fg <jobid>\n");
		return;
	}

	if(args[1] != NULL)
		strcpy(t1,args[1]);

	jobs(0);

	int jobid = atoi(t1);

	if(jobid >= active)
	{
		fprintf(stderr, "Job Does Not Exist\n");
		return;
	}
	
	kill(job_proc[jobid].pid,SIGCONT);

	printf("%s\n", job_proc[jobid].command);

	pid = job_proc[jobid].pid;
	wpid = waitpid(pid, &status, WUNTRACED);

	while(1)
	{
		if(WIFEXITED(status) && WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
			continue;
		}
		break;
	}

	for(itr = 0; itr<num_background_proc;itr++)
	{
		if(back_proc[itr].pid == job_proc[jobid].pid)
		{
			back_proc[itr].state = -1;
		}
	}
}

void bg()
{
	char t1[10];
	int itr,status;
	
	if(args[1] == NULL)
	{
		fprintf(stderr, "Usage: bg <jobid>\n");
		return;
	}

	if(args[1] != NULL)
		strcpy(t1,args[1]);

	jobs(0);

	int jobid = atoi(t1);

	if(jobid >= active)
	{
		fprintf(stderr, "Job Does Not Exist\n");
		return;
	}
	
	kill(job_proc[jobid].pid,SIGCONT);
}

void overkill()
{
	jobs(0);

	for (int itr=0; itr<active; itr++)
	{
		kill(job_proc[itr].pid,9);
	}

	
	for(int j=0; j<num_background_proc ; j++)
	{
		 back_proc[j].state = -1;
	}
}