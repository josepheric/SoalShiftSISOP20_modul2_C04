#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <wait.h>


int main(int argc, char	**argv) {
	int i, flag=1;
	for (i=0; argv[1][i]!='\0'; i++)
	{
	if (isdigit(argv[1][i]) == 0 && strcmp(argv[1],"*") != 0)
	flag=0;
	}

	for (i=0; argv[2][i]!='\0'; i++)
	{
	// check for decimal digits
	if (isdigit(argv[2][i]) == 0 && strcmp(argv[2],"*") != 0)
	flag=0;
	}
	for (i=0; argv[3][i]!='\0'; i++)
	{
	// check for decimal digits
	if (isdigit(argv[3][i]) == 0 && strcmp(argv[3],"*") != 0)
	flag=0;
	}

	if (atoi(argv[1]) >=60 || atoi(argv[2]) >= 60 || atoi(argv[3]) >= 60 && flag==1)
	flag=0;

	if(flag==0)
	{
	printf("Input Parameter Error\n");
	exit(EXIT_FAILURE);
	}

	struct stat a;
	if(stat(argv[4],&a) != 0){
    printf("Path tidak ditemukan\n");
    exit(EXIT_FAILURE);
  }

pid_t pid, sid;
pid = fork();
if (pid < 0) {
exit(EXIT_FAILURE);
}
if (pid > 0) {
exit(EXIT_SUCCESS);
}

umask(0);

sid = setsid();
if (sid < 0) {
exit(EXIT_FAILURE);
}

if ((chdir("/")) < 0) {
exit(EXIT_FAILURE);
}


close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

while (1)
{
//masih belum paham cara buat program yang seperti crontabnya
}

}
