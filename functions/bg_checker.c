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

void check_back()
{
	int status;
	pid_t wpid;

	/*for(int j = 0; j < num_background_proc; j++)
	{
			printf("%s %d %s %d\n",GREEN,back_proc[j].jobid,  back_proc[j].command, wpid);
			//print_prompt();
	}*/

	while((wpid = waitpid(-1, &status, WNOHANG)) > 0) // Checks for the child processes which have changed there status. 
	{
			//returns true if the child process was terminated by a signal.
			//returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main().
		//if(WIFEXITED(status) == 0 || WIFSIGNALED(status) == 0)
		{
			for(int j = 0; j < num_background_proc; j++)
			{
				if(back_proc[j].pid == wpid)
				{
					printf("%s[%d]+	Done\t\t PID %d\n",GREEN,back_proc[j].jobid, wpid);
					//print_prompt();
				}
			}
		}
					//printf("%s[]+	Done\t\t\t with pid %d\n",GREEN,wpid);
	}
}