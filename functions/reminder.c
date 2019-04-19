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

void remindme(char command[])
{
	if(args[1] == NULL || strcmp(args[1],"") == 0)
	{
		printf("Error : specify time\n");
		return;
	}

	int flag = 0,j=0;
	char message[BUFSIZE];
	int time = atoi(args[1]);
	pid_t pid;
	pid = fork();

	if (pid < 0)
	{
		perror("Error in FORK: ");
	}

	else if (!pid)
	{
		for(int i=0;i<strlen(command)-1;i++)
		{
			if(command[i] == '\"' || command[i] == '\'')
			{
				flag = 1;
				continue;
			}

			if(flag == 1)
			{
				message[j++]=command[i];
			}
		}
		message[j] = '\0';
		if (flag == 0)
		{
			printf("\nError: Use Quotes for the Message\n");
		}
		if(flag==1)
		{
			sleep(time);
			printf("\n%s%s\n",YELLOW,message);
		}
		print_prompt();
		exit(0);
	}
}