#ifndef declarations
#define declarations

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

#define clear() printf("\033[H\033[J")
#define ARG_NUM 16
#define BUFSIZE 1024
#define INPBUF 128
#define ALLOW 32
#define RED "\x1b[91m"
#define GREEN "\x1b[92m"
#define YELLOW "\x1b[93m"
#define BLUE "\x1b[94m"
#define DEF "\x1B[0m"
#define MAGENTA "\x1b[95m"
#define CYAN "\x1b[96m"

int num_args;
int flag_exit;
int flag_background;
int home_len;
int inBackground;
int mypid;
int active;
int num_background_proc; 
int total_jobs;
int num_comms,num_pipes;
int stdin_cpy, stdout_cpy;
//int fd_pipe[2];
//int if_pipe;
char delimit[10];
char home[BUFSIZE];
char prev_loc[BUFSIZE];
char cwd_str[BUFSIZE];
char* user;
char host[BUFSIZE];
char *input_str, *input_str_mod;
char* args[ARG_NUM];
char* commands[ALLOW];
char* pipe_commands[ALLOW];
pid_t pid, wpid;
char tmp[ARG_NUM][BUFSIZE];

struct _instr
{
    char * argval[INPBUF];
    int argcount;
};
typedef struct _instr instruction;

struct background{
	int pid;
    int jobid;
    int state;
    char status;
    char command[BUFSIZE];
};
typedef struct background background;

struct job{
	int pid;
    int jobid;
    char command[BUFSIZE];
};
typedef struct job job;

background back_proc[ALLOW];
background job_proc[ALLOW];

void input_semi();
void input(int num);
void getUser();
void getHost();
void print_prompt();
void func_cd(char* path);
void echo();
void func_pwd(char* str, int flag_command);
void print_file(struct dirent* name);
void getPermissions(mode_t struc);
void func_ls();
void func_lsl();
void executables();
void pinfo();
void check_back();
void remindme(char command[]);
void clock_time();
void func_exit();
void func_redirect();
void input_pipe(int num);
int check_redirect(int num);
void stopSignal();
void intSignal();
void piping();
void set_env();
void unset_env(int to_print);
void jobs(int to_print);
void kjob();
void fg();
void bg();
void overkill();

#endif