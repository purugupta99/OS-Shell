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

void clock_time()
{
	if(args[1] == NULL || strcmp(args[1],"") == 0 || args[2] == NULL || args[3] == NULL || args[4] == NULL)
	{
		printf("Error: No Flags Found\n");
		return;
	}

	if(strcmp(args[1],"-t") != 0 || strcmp(args[3],"-n") != 0)
	{
		printf("Error: Wrong Flag\n");
		return;
	}
	else
	{
		if(args[2] != NULL && args[4] != NULL)
		{
			char path[BUFSIZE] = "/sys/class/rtc/rtc0";

			char time[BUFSIZE]; 
			char date[BUFSIZE]; 

			int seconds = atoi(args[2]);
			int max = atoi(args[4]);
			int count = 0;

			strcpy(time,path);
			strcat(time,"/time");

			strcpy(date,path);
			strcat(date,"/date");

			char t[20],d[20];

			//printf("%d",max);
			while(count < max)
			//while(1)
			{
				FILE * dt = fopen(date,"r");
				FILE * tm = fopen(time,"r");
				fscanf(dt,"%s",d);
				fscanf(tm,"%s",t);

				count += seconds;
				printf("%s %s\n",d,t);
				sleep(seconds);
				fclose(tm);
				fclose(dt);

			}

		}
		else if(args[2] == NULL)
		{
			printf("Error : Specify Time\n");
			return;
		}
		else if(args[4] == NULL)
		{
			printf("Error : Specify Max Limit\n");
			return;
		}
	}
}