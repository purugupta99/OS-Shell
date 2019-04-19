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

void getUser()
{
	register struct passwd *pw;
	register uid_t uid;

	uid = geteuid();
	pw = getpwuid(uid);

	user = pw -> pw_name;
}

void getHost()
{
	gethostname(host,BUFSIZE);
}