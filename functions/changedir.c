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

void func_cd(char* path)
{
	char abs_path[BUFSIZE];
	//printf("%s\n",path);
	if (path != NULL && strcmp(path,"") != 0)
	{
		strcpy(abs_path,path);
	}

	if(path == NULL || strcmp(path,"~") == 0 || strcmp(path,"\n") == 0 || strcmp(path,"") == 0)
	{
		strcpy(abs_path,home);
	}

	else if(strcmp(path,"-") == 0)
	{
		strcpy(abs_path,prev_loc);
	}

	func_pwd(prev_loc,0);
	
	int success = chdir(abs_path);

    if(success == 0) // path could be changed if cd successful
    {
    	func_pwd(cwd_str,0);
    }
    else perror("Error in cd: ");
}
