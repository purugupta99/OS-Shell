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

void print_file(struct dirent* name)
{
	if(name->d_type == DT_REG)
	{
		printf("%s%s",GREEN, name->d_name);
	}
	else if(name->d_type == DT_DIR)
	{
		printf("%s%s/",CYAN, name->d_name);
	}
	else
	{
		printf("%s%s",RED,name->d_name);
	}
}

int file_select(const struct dirent *checker)
{
	if(checker->d_name[0]=='.')
		return 0; 
	else
		return 1;
}

void func_ls(char* flags)
{
	int i,file_num = 0;
	struct dirent **list;

	if(flags == NULL || strcmp(flags,"")==0 || strcmp(flags,"\n")==0)
	{
		file_num = scandir(".",&list,file_select,alphasort);
	}
	else if(strcmp(flags,"-a") == 0)
	{
		file_num = scandir(".",&list,0,alphasort);
	}

	if(file_num >= 0)
	{
		printf("%s-+-+- Total %d objects in this directory\n",CYAN,file_num);
		for(i = 0;i < file_num; i++)
		{
			//if(strcmp(list[i]->d_name,".")!=0 && strcmp(list[i]->d_name,"..")!=0)
			//{
			print_file(list[i]);
			printf("\t");
			//}

			if((i+1)%6==0) 
			{
				printf("\n");
			}
		}
		printf("\n");
	}
	else
	{
		perror("Error in ls: ");
	}
}

void getPermissions(mode_t struc)
{
	char type = '*';

	if(S_ISREG(struc)) 
	{
		type = '-';
	}
	else if(S_ISDIR(struc))
	{
		type = 'd';
	}
	else if(S_ISLNK(struc))
	{
		type = 'l';
	}
	else if(S_ISBLK(struc))
	{
		type = 'b';
	}
	else if(S_ISCHR(struc))
	{
		type = 'c';
	}
	else if(S_ISFIFO(struc))
	{
		type = 'f';
	}
	else if(S_ISSOCK(struc))
	{
		type = 's';
	}
	printf("%s%c",RED,type);

	printf("%s%c",GREEN,(struc & S_IRUSR) ? 'r' : '-');
	printf("%s%c",GREEN,(struc & S_IWUSR) ? 'w' : '-');
	printf("%s%c",GREEN,(struc & S_IXUSR) ? 'x' : '-');
	printf("%s%c",GREEN,(struc & S_IRGRP) ? 'r' : '-');
	printf("%s%c",GREEN,(struc & S_IWGRP) ? 'w' : '-');
	printf("%s%c",GREEN,(struc & S_IXGRP) ? 'x' : '-');
	printf("%s%c",GREEN,(struc & S_IROTH) ? 'r' : '-');
	printf("%s%c",GREEN,(struc & S_IWOTH) ? 'w' : '-');
	printf("%s%c",GREEN,(struc & S_IXOTH) ? 'x' : '-');
}

void func_lsl(char *flags)
{
	// - -rwxrwxr-x 1 user user  8872 Jan 26 10:19 a.out*
	int i,file_num = 0,sz = 0;
	struct dirent **list;
	struct stat file;
	char datestring[256];
	struct tm time_format;

	if(strcmp(flags,"-la") == 0 || strcmp(flags,"-al") == 0)
	{
		file_num = scandir(".",&list,0,alphasort);
	}
	else if((args[1] != NULL && args[2] != NULL && strcmp(args[1],"-l")==0 && strcmp(args[2],"-a")==0) || (args[1] != NULL && args[2] != NULL && strcmp(args[1],"-a")==0 && strcmp(args[2],"-l")==0))
	{
		file_num = scandir(".",&list,0,alphasort);
	}
	else if (strcmp(flags,"-l") == 0)
	{
		file_num = scandir(".",&list,file_select,alphasort);
	}

	if(file_num > 0)
	{
		printf("%s-+-+- Total %d objects in this directory\n",CYAN,file_num);
		
		for(i=0;i<file_num;i++)
		{
			if(strcmp(list[i]->d_name,".")==0 || strcmp(list[i]->d_name,"..")==0)
			{
				continue;
			}
			else if(stat(list[i]->d_name,&file)==0)
			{
				sz += file.st_blocks;
				getPermissions(file.st_mode);
				printf(" %2lu ", file.st_nlink); 
				printf("%s ",(getpwuid(file.st_uid))->pw_name);
				printf("%s ",(getgrgid(file.st_gid))->gr_name);
				printf("%7lld ", (long long int)file.st_size);

				localtime_r(&file.st_mtime, &time_format);
				strftime(datestring, sizeof(datestring), "%b %d %H:%M ", &time_format);
				printf("%s ",datestring);

				print_file(list[i]);
				printf("\n");
			}
		}
		printf("%s-+-+- Total %d blocks\n",CYAN,sz/2);
	}
	else
	{
		printf("%s-+-+- Empty directory\n",CYAN);
	}
}