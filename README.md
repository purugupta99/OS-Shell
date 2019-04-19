                                **OS Shell**

**To execute the shell :-**

-    To compile: make
-    To run: ./Cshell
-    Clean: make clean

**FILES :-**

- bg\_checker.c – contains check\_back() to check when does a background process exits
- change_dir.c – contains func\_cd() to implement the cd function
- clock\_time.c – contains clock\_time to run a simple clock command
- env_var.c - contains set\_env() and unset\_env() to set and unset variables
- executable.c – contains executables() to run binary files
- getinput.c – contains input\_semi(), input\_pipe() for semicolon and '|' separated commands and input() for parsing the arguments and check\_redirect() to check if the command is a redirecting command
- getuser.c – contains getUser() and getHost() to return the username and system name of the PC
- job.c - contains jobs(), kjob(), bg() and fg() to list all background processes, send various signals to processes, send bg and fg signal to currently running processes.
- list\_dir.c – contains print\_file(), file\_select(), func\_ls(), getPermissions() and func\_lsl() to implement the ls command with -l and -a flags
- pinfo.c – contains pinfo() to implement the pinfo command
- piping.c - contains piping() to implement the pipe functionality
- pr\_echo.c – contains echo() to implement the echo command
- present\_dir.c – contains func\_pwd() to implement the pwd command
- print\_prompt.c – contains print\_prompt() to print the shell prompt of format &lt;**username@system\_name:curr\_dir**&gt;
- redirection.c - contains func\_redirect() to implement redirection functionality 
- reminder.c – contains remindme() to create reminders from the shell
- shell.c – contain the main() to execute all functionalities of the shell
- signals.c - contains the intSignal() and stopSignal() to send SIGINT and SIGSTOP to processes when Ctrl+C and Ctrl+Z is pressed
- declarations.h – contains all function declarations, definitions and global variables
- Makefile – contains all the instructions to compile the above mentioned .c files