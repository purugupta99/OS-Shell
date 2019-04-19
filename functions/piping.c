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

// void piping()
// {
// 	int p[2],fd_in;

// 	for(int m=0;m < num_pipes;m++)
// 	{	
// 		input(m);

// 		//int previous = 1, next = 1;
// 		if(m != 0)
// 		{
// 			dup2(fd_in,0);
// 		}

// 		if(m+1 != num_pipes)
// 		{
// 			dup2(p[1],1);
// 		}


// 		if(previous)
// 		{
// 			close(fd_pipe[1]);
// 			dup2(fd_pipe[0],0);
// 			close(fd_pipe[0]);
// 		}

// 		if(next)
// 		{
// 			if(pipe(fd_pipe) != 0)
// 			{
// 				perror("Error in Piping: ");
// 			}
// 			dup2(fd_pipe[1],1);
// 		}

// 		int if_redirect = check_redirect(m);

// 				//printf("%d\n",if_redirect );
// 		if( if_redirect )
// 		{
// 					//printf("hi\n");
// 			func_redirect();
// 		}

// 		if(args[0] == NULL)
// 		{
// 			continue;
// 		}
// 		else if(strcmp(args[0],"clear")==0 && flag_background == 0)
// 		{
// 			clear();
// 		}
// 		else if(strcmp(args[0],"cd") == 0 && flag_background == 0)
// 		{
// 			char* path = args[1];
// 			func_cd(path);
// 		}
// 		else if(strcmp(args[0],"pwd")==0 && flag_background == 0)
// 		{
// 			func_pwd(cwd_str,1);
// 		}
// 		else if(strcmp(args[0],"echo")==0 && flag_background == 0)
// 		{
// 			echo();
// 		}
// 		else if(strcmp(args[0],"pinfo")==0 && flag_background == 0)
// 		{
// 			pinfo();
// 		}
// 		else if(strcmp(args[0],"ls")==0 && flag_background == 0)
// 		{
// 			char* flag = args[1];
// 			char* flag2 = args[2];
// 			if(flag != NULL && (strcmp(flag,"-l")==0 || strcmp(flag,"-la")==0 || strcmp(flag,"-al")==0))
// 			{
// 				func_lsl(flag);
// 			}
// 			else if(flag != NULL && flag2 != NULL && strcmp(flag,"-a")==0 && strcmp(flag2,"-l")==0)
// 			{
// 				func_lsl(flag);
// 			}
// 			else
// 			{
// 				func_ls(flag);
// 			}
// 		}
// 		else if(strcmp(args[0],"remindme") == 0 && flag_background == 0)
// 		{
// 			remindme(input_str_mod);
// 		}
// 		else if(strcmp(args[0],"clock")==0 && flag_background == 0)
// 		{
// 			clock_time();
// 		}
// 		else if(strcmp(args[0],"exit")==0 && flag_background == 0)
// 		{
// 			func_exit();
// 		}
// 		else if(strcmp(args[0],"set_env")==0 && flag_background == 0)
// 		{
// 				//printf("%s %s %s\n", args[0],args[1],args[2]);
// 			set_env();
// 		}
// 		else if(strcmp(args[0],"unset_env")==0 && flag_background == 0)
// 		{
// 				//printf("%s %s\n", args[0],args[1]);
// 			unset_env();
// 		}
// 		else if(strcmp(args[0],"jobs")==0 && flag_background == 0)
// 		{
// 				//printf("%s %s\n", args[0],args[1]);
// 			jobs();
// 		}
// 		else
// 		{
// 			executables();
// 		}

// 		for(int a=0;a<ARG_NUM;a++)
// 		{
// 			args[a] = NULL;
// 		}
// 	}

// }

void piping()
{
	//printf("hi\n");

	int fd_in;
	int p[2];
	for(int m=0;m < num_pipes;m++)
	{	
		input(m);

		

		pipe(p);

		//if_pipe = 1;
		pid = fork();
		if(pid == 0)
		{
			if(m != 0)
			{
				dup2(fd_in,0);
			}

			if(m+1 != num_pipes)
			{
				dup2(p[1],1);
			}

			close(p[0]);

			int if_redirect = check_redirect(m);

				//printf("%d\n",if_redirect );
			if( if_redirect )
			{
					//printf("hi\n");
				func_redirect();
			}

			if(args[0] == NULL)
			{
				continue;
			}
			else if(strcmp(args[0],"clear")==0 && flag_background == 0)
			{
				clear();
			}
			else if(strcmp(args[0],"cd") == 0 && flag_background == 0)
			{
				char* path = args[1];
				func_cd(path);
			}
			else if(strcmp(args[0],"pwd")==0 && flag_background == 0)
			{
				func_pwd(cwd_str,1);
			}
			else if(strcmp(args[0],"echo")==0 && flag_background == 0)
			{
				echo();
			}
			else if(strcmp(args[0],"pinfo")==0 && flag_background == 0)
			{
				pinfo();
			}
			else if(strcmp(args[0],"ls")==0 && flag_background == 0)
			{
				char* flag = args[1];
				char* flag2 = args[2];
				if(flag != NULL && (strcmp(flag,"-l")==0 || strcmp(flag,"-la")==0 || strcmp(flag,"-al")==0))
				{
					func_lsl(flag);
				}
				else if(flag != NULL && flag2 != NULL && strcmp(flag,"-a")==0 && strcmp(flag2,"-l")==0)
				{
					func_lsl(flag);
				}
				else
				{
					func_ls(flag);
				}
			}
			else if(strcmp(args[0],"remindme") == 0 && flag_background == 0)
			{
				remindme(input_str_mod);
			}
			else if(strcmp(args[0],"clock")==0 && flag_background == 0)
			{
				clock_time();
			}
			else if(strcmp(args[0],"quit")==0 && flag_background == 0)
			{
				func_exit();
			}
			else if(strcmp(args[0],"set_env")==0 && flag_background == 0)
			{
				for(int itr = 0;itr <3;itr++)
				{
					if(args[itr] != NULL)
					{
						strcpy(tmp[itr],args[itr]);
					}
				}
					//printf("%s %s\n", tmp[0],tmp[1]);
				unset_env(0);
				set_env();
			}
			else if(strcmp(args[0],"unset_env")==0 && flag_background == 0)
			{
				for(int itr = 0;itr <2;itr++)
				{
					if(args[itr] != NULL)
					{
						strcpy(tmp[itr],args[itr]);
					}
				}
					//printf("%s %s\n", tmp[0],tmp[1]);
				unset_env(1);
			}
			else if(strcmp(args[0],"jobs")==0 && flag_background == 0)
			{
				//printf("%s %s\n", args[0],args[1]);
				jobs(1);
			}
			else if(strcmp(args[0],"kjob")==0 && flag_background == 0)
			{
					//printf("%s %s\n", args[0],args[1]);
				kjob();
			}
			else if(strcmp(args[0],"fg")==0 && flag_background == 0)
			{
				fg();
			}
			else if(strcmp(args[0],"bg")==0 && flag_background == 0)
			{
				bg();
			}
			else if(strcmp(args[0],"overkill")==0 && flag_background == 0)
			{
				overkill();
			}
			else
			{
				// for(int l=0;l<num_args;l++)
				// {
				// 	printf("%s\n", args[l]);
				// }
				executables();
			}

			for(int a=0;a<ARG_NUM;a++)
			{
				args[a] = NULL;
			}

			exit(0);
		}

		else
		{
			//if_pipe = 0;
			wait(NULL);
			close(p[1]);
		//fd_in=p[0];
			dup2(p[0],fd_in);
		}
	}
}
