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

void func_pwd(char* str, int flag_command)
{
	char temp[BUFSIZE];
	char* path = getcwd(temp,sizeof(temp));

	if(path != NULL)
	{
		strcpy(str,temp);
		if(flag_command==1)
		{
			printf("%s%s\n",RED,cwd_str);
		}
	}
	else perror("Error in getcwd(): ");
}
