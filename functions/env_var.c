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

void set_env()
{
	if(tmp[2] == NULL || args[3]!=NULL){
		//printf("%s %s %s\n", tmp[0],tmp[1],tmp[2]);
		fprintf(stderr, "Usage: setenv <varible> <value>\n");
		return ;
	}

	if(getenv(tmp[1])==NULL)
	{
		//printf("%s %s %s\n", tmp[0],tmp[1],tmp[2]);

		//printf("%s %s %s\n", tmp[0],tmp[1],tmp[2]);
		if(setenv(tmp[1],tmp[2],1) != 0)
		{
			perror("Error in Set: ");
		}
	}
}

void unset_env(int to_print)
{
		//printf("%s %s \n", tmp[0],tmp[1]);
	if(tmp[1] == NULL || args[2]!=NULL){
		if(to_print == 1)
		{
			fprintf(stderr, "Usage: unset_env <varible>\n");
		}
	}

	if(unsetenv(tmp[1])!=0)
	{

		perror("Error in Unset: ");
	}
}