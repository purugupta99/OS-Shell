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

void print_prompt()
{
	int cwd_len = strlen(cwd_str);
	int i = 0;

	while(home[i] == cwd_str[i] && i<home_len && i<cwd_len)
	{
		i++;
	}

	printf("%s<%s@%s:",BLUE,user,host);
	if(i==home_len)
	{
		printf("~");
		for (int j=i;j<cwd_len;j++)
		{
			printf("%c",cwd_str[j]);
		}
	}
	else
	{
		printf("%s",cwd_str);
	}
	printf("> %s",DEF);
}

void func_exit()
{
	flag_exit = 1;
	return;
}


