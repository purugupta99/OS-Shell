#include "functions/declarations.h"

int main(int argc, char const *argv[])
{
	signal(SIGINT,intSignal);
	//signal(EOF,SIG_IGN);
	signal(SIGTSTP,stopSignal);

	int p[2];
	int fd_in;
	num_args = 0;
	flag_exit = 0;
	flag_background = 0;
	home_len = 0;
	num_background_proc = 0;
	total_jobs = 0;
	//if_pipe = 0;
	strcpy(delimit," \t\r\n\v\f");

	int exec_ret;
	clear();
	func_pwd(home,0);
	strcpy(prev_loc,home);
	home_len = strlen(home);
	mypid = getpid();
	getUser();
	getHost();

	stdin_cpy = dup(0);
	stdout_cpy = dup(1);

	while (flag_exit == 0) 
	{
		//printf("%d\n",mypid);
		num_comms = 0;
		func_pwd(cwd_str,0);
		print_prompt();
		input_semi();
		check_back();

		/*for (int i=0;i<num_args;i++)
		{
			printf("%s\n",args[i]);
		}*/
		for(int l=0;l<num_comms;l++)
		{
			input_pipe(l);

			/*printf("%d\n",num_pipes);
			for(int v=0;v<num_pipes;v++)
			{
				printf("%s\n", pipe_commands[v]);
			}*/


			



				/*printf("%d\n",num_args);
				for(int v=0;v<num_args;v++)
				{
					printf("%s ", args[v]);
				}
				printf("\n");*/

			if(num_pipes > 1)
			{
				//printf("hi %d %d\n", m, num_pipes);
				piping();
			}
			else
			{

				input(0);
				int if_redirect = check_redirect(l);


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
					//printf("%s %s\n", args[1], args[2]);

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
					executables();
				}

				for(int a=0;a<ARG_NUM;a++)
				{
					args[a] = NULL;
				}
				
			}
			dup2(stdin_cpy,0);
			dup2(stdout_cpy,1);
		}
	}

	printf("%sBYE\n",RED);
	return 0;
}
