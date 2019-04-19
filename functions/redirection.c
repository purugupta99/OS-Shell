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

void func_redirect()
{
	int input=0,output=0,append=0,check=0;

	int file_d;
	char out_file[BUFSIZE],in_file[BUFSIZE],command[BUFSIZE];

	/*printf("%d\n",num_args);
	for(int v=0;v<num_args;v++)
	{
		printf("%s\n", args[v]);
	}*/

	int i;
	for(i=0;i<num_args;i++)
	{
		if(args[i] != NULL && strcmp(args[i],">") == 0)
		{
			output = i;
			strcpy(out_file,args[i+1]);
			args[i]=NULL;
			args[i+1]=NULL;
			check++;
			//num_args-=2;
		}
		if (args[i] != NULL && strcmp(args[i],">>") == 0)
		{
			append = i;
			strcpy(out_file,args[i+1]);
			args[i]=NULL;
			args[i+1]=NULL;
			check++;
			//num_args-=2;
		}
		if (args[i] != NULL && strcmp(args[i],"<") == 0)
		{
			char temp[BUFSIZE];
			strcpy(temp,args[0]);
			input = i;
			strcpy(in_file,args[i+1]);
			strcpy(args[0],temp);
			args[i]=NULL;
			args[i+1]=NULL;
			check++;
			//num_args-=2;
		}
	}

	if(check == 1) num_args-=2;
	if(check == 1) num_args-=4;
	
	//printf("%d %d %d\n",input,output,append);

	if(input != 0)
	{
		file_d = open(in_file,O_RDONLY);
		if(file_d == -1)
		{
			perror("Unable to Open File: ");
			exit(0);
		}
		dup2(file_d,0);
		close(file_d);
	}
	
	if(output != 0 || append != 0)
	{
		if(output)
		{
			file_d = open(out_file,O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if(append)
		{
			file_d = open(out_file,O_WRONLY | O_CREAT | O_APPEND, 0644); 
		}

		if(file_d == -1)
		{
			perror("Unable to Open/Create File: ");
			//exit(0);
		}
		dup2(file_d,1);
		close(file_d);
	}
}