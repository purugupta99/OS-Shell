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

void echo()
{
	if (args[1] == NULL)
	{
		printf("\n");
	}

	int k = 1;
	while(k < num_args)
	{
		if(args[k][0] == '\"' || args[k][0] == '\'')
		{
			int len = strlen(args[k]);
			int j = 0;
			if(args[k][len-1] == '\'' || args[k][len-1] == '\"')
			{
				for(j=1;j<len-1;j++)
				{
					printf("%c",args[k][j]);
				}
			}
			else
			{
				for(j=1;j<len;j++)
				{
					printf("%c",args[k][j]);
				}
			}
			printf(" ");
		}

		else if(args[k][0] == '$')
		{
			char* address = getenv(args[k]+1);

			if(address != NULL)
			{
				printf("%s ",address);
			}
			else
			{
				printf(" ");
			}
		}

		else
		{
			int len = strlen(args[k]);
			int j = 0;
			if(args[k][len-1] == '\'' || args[k][len-1] == '\"')
			{
				for(j=0;j<len-1;j++)
				{
					printf("%c",args[k][j]);
				}
			}
			else
			{
				for(j=0;j<len;j++)
				{
					printf("%c",args[k][j]);
				}
			}
			printf(" ");
		}

		k++;
	}
	printf("\n");
}
