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

void intSignal()
{
	//printf("%d\n", pid);
	if(pid != 0)
	{
		int temp = pid;
		kill(pid, SIGINT);
		pid = 0;
	}
}

void stopSignal()
{
	if(pid!=0)
	{
		int flag = 1;
		for(int i=0;i<num_background_proc;i++)
		{
			if(back_proc[i].pid == pid)
			{
				flag = 0;
				printf("\n%s\t\t%s\t[%d]\n","Stopped",back_proc[i].command,back_proc[i].pid);
				break;
			}
		}
		if(flag)
		{
			back_proc[num_background_proc].pid = pid;
			back_proc[num_background_proc].state = 1;
			strcpy(back_proc[num_background_proc].command,args[0]);
			back_proc[num_background_proc].jobid = num_background_proc;

			printf("\n%s\t\t%s\t[%d]\n","Stopped",back_proc[num_background_proc].command,back_proc[num_background_proc].pid);

			num_background_proc++;
		}

		int temp = pid;
		kill(pid, SIGSTOP);
		pid = 0;
	}
}