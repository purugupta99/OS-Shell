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

void executables()
{
	//char temp[BUFSIZE];

	char temp_args[ARG_NUM][BUFSIZE];

	/*for(int l=0;l<num_args;l++)
	{
		printf("%s\n", args[l]);
	}*/
	for(int l=0;l<num_args;l++)
	{
		strcpy(temp_args[l],args[l]);
	}

	//strcpy(temp,args[0]);
	
	// flag_background = 0;
	// for(int l=0;l<num_args;l++)
	// {
	// 	printf("%s\n", args[l]);
	// }
	
	if(args[num_args-1] != NULL && strcmp(args[num_args-1],"&")==0)
	{
		flag_background = 1;
		args[num_args-1] = NULL;
		num_args--;
	}
	

	//pid_t pid, wpid;
	int status;
	//all_proc[total_jobs].command = args[0];
	
	//strcpy(all_proc[total_jobs].command,temp);
	//all_proc[total_jobs].jobid = total_jobs; 

	
	/*for(int l=0;l<num_args;l++)
	{
		printf("after %s\n", args[l]);
	}*/

	//if(!if_pipe)
	pid = fork();
	


	if(pid < 0)
	{
		perror("Error in Fork: ");
	}
	else if(!pid)
	{
		//strcpy(args[0],"cat");


		
		for(int l=0;l<num_args;l++)
		{
			strcpy(args[l],temp_args[l]);
		}


		/*for(int i=0;i<num_args;i++)
		{
			if(args[i]!=NULL)
			{
				printf("%s\n",args[i]);
			}
		}*/
		if(flag_background == 1)
		{
			setpgid(0,0);
		}


		if(execvp(args[0],args) == -1)
		{
			perror("Error in Execvp: ");
			//return;
		}
		
		/*for(int i=0;i<num_args;i++)
		{
			if(args[i]!=NULL)
			{
				printf("%s\n",args[i]);
			}
		}*/
		
		exit(0);
	}
	else
	{
		//all_proc[total_jobs].pid = pid;

		if(flag_background == 0)
		{
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
			/*
			while(!WIFEXITED(status) && !WIFSIGNALED(status))
			{
				wpid = waitpid(pid, &status, WUNTRACED);
			}*/
		}
		else if(flag_background == 1)
		{
			//signal(SIGINT, SIG_IGN);
			//printf("%d %s %d\n",pid,command[i].argval[0],num_background_proc);
			back_proc[num_background_proc].pid = pid;
			//printf("%s\n",args[0]);
			back_proc[num_background_proc].state = 1;
			strcpy(back_proc[num_background_proc].command,temp_args[0]);
			back_proc[num_background_proc].jobid = num_background_proc;

			//printf("%d %s %d\n",back_proc[num_background_proc].pid,back_proc[num_background_proc].command,num_background_proc);

			printf("%sProcess running in Background. PID:%d\n",GREEN,pid);
			printf("[%d]+\t\t\t PID %d\n",back_proc[num_background_proc].jobid,pid);
			
			num_background_proc++;
			pid = 0;
		}
	}
	
	//printf("[%d]\t%s [%d]\n",all_proc[total_jobs].jobid,all_proc[total_jobs].command,all_proc[total_jobs].pid);
	total_jobs++;
	pid = 0;
	flag_background = 0;
	//free(input_str_mod);
}