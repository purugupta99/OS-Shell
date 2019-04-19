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

void input_semi()
{
	// for(int a=0;a<ARG_NUM;a++)
	// {
	// 	args[a] = NULL;
	// }

	fflush(stdout);
	//fflush(stdin);
	free(input_str);

	int j=0;
	ssize_t size = 0;
	int characters = getline(&input_str,&size,stdin);
	input_str[characters] = '\0';

	char * semi_token = strtok(input_str,";");
	while(semi_token != NULL && num_comms-1 < ALLOW)
	{
		commands[num_comms++] = semi_token;
		semi_token = strtok(NULL,";");
	}
}

void input_pipe(int num)
{
	fflush(stdout);
	char str[BUFSIZE];
	strcpy(str,commands[num]);
	num_pipes = 0;

	char* token = strtok(str,"|");

	while(token != NULL && num_pipes-1 < ARG_NUM)
	{
		pipe_commands[num_pipes++] = token;
		token = strtok(NULL,"|");
	}
	pipe_commands[num_pipes] = NULL;
}

void input(int num)
{
	fflush(stdout);
	char str[BUFSIZE];
	//printf("%s\n", pipe_commands[num]);
	strcpy(str,pipe_commands[num]);
	num_args = 0;
	flag_background = 0;
	//input_str_mod = (char *) malloc((strlen(str))*sizeof(char));

    //strcpy(input_str_mod,str);

	char* token = strtok(str,delimit);

	while(token != NULL && num_args-1 < ARG_NUM)
	{
		args[num_args++] = token;
		token = strtok(NULL,delimit);
		if(strcmp(args[num_args-1],"&")==0)
		{
			flag_background = 1;
			return;
		}
	}
	// for(int l=0;l<num_args;l++)
	// {
	// 	printf("%s\n",args[l]);
	// }
	args[num_args] = NULL;
}

/*int check_redirect(int num)
{
		//printf("%s %s %s\n", args[0],args[1],args[2]);
	int i = 0;
	while(pipe_commands[num][i] != '\0')
	{
		if(pipe_commands[num][i] == '>' || pipe_commands[num][i] == '<')
		{
			return 1;
		}
		i++;
	}
	return 0;
}*/

/*int check_cmd_pipe(int num)
{
		//printf("%s %s %s\n", args[0],args[1],args[2]);
	int i = 0;
	while(commands[num][i] != '\0')
	{
		if(commands[num][i] == '|')
		{
			return 1;
		}
	}
	return 0;*/
int check_redirect(int num)
{
	int i=0;
	if(args[0] == NULL)
	{
		return 0;
	}
	else
	{
		while(args[i] != NULL)
		{
			if(strcmp(args[i],">") == 0 || strcmp(args[i],"<") == 0 || strcmp(args[i],">>") == 0)
			{
				return 1;
			}
			i++;
		}
		return 0;
	}
}