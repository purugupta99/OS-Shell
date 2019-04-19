Cshell : bg_checker.o changedir.o clock_time.o env_var.o executable.o getinput.o getuser.o jobs.o list_dir.o pinfo.o piping.o pr_echo.o print_prompt.o present_dir.o reminder.o redirection.o shell.o signals.o
	gcc $^ -o Cshell

bg_checker.o : functions/bg_checker.c
	gcc -c functions/bg_checker.c

changedir.o : functions/changedir.c
	gcc -c functions/changedir.c

clock_time.o : functions/clock_time.c
	gcc -c functions/clock_time.c

executable.o : functions/executable.c
	gcc -c functions/executable.c

env_var.o : functions/env_var.c
	gcc -c functions/env_var.c

getinput.o : functions/getinput.c
	gcc -c functions/getinput.c

getuser.o : functions/getuser.c
	gcc -c functions/getuser.c

jobs.o : functions/jobs.c
	gcc -c functions/jobs.c

list_dir.o : functions/list_dir.c
	gcc -c functions/list_dir.c

pinfo.o : functions/pinfo.c
	gcc -c functions/pinfo.c

piping.o : functions/piping.c
	gcc -c functions/piping.c

pr_echo.o : functions/pr_echo.c
	gcc -c functions/pr_echo.c

print_prompt.o : functions/print_prompt.c
	gcc -c functions/print_prompt.c

present_dir.o : functions/present_dir.c
	gcc -c functions/present_dir.c

redirection.o : functions/redirection.c
	gcc -c functions/redirection.c

reminder.o : functions/reminder.c
	gcc -c functions/reminder.c

shell.o : shell.c
	gcc -c shell.c

signals.o : functions/signals.c
	gcc -c functions/signals.c

clean : 
	rm -f changedir.o clock_time.o env_var.o getuser.o jobs.o pr_echo.o print_prompt.o redirection.o shell.o bg_checker.o executable.o getinput.o list_dir.o pinfo.o piping.o present_dir.o reminder.o signals.o Cshell