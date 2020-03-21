#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


int main(int argc, char	**argv) {
	int i, flag=1;
	for (i=0; argv[1][i]!='\0'; i++)
	{
	if (isdigit(argv[1][i]) == 0 && strcmp(argv[1],"*") != 0)
	flag=0;
	}
	for (i=0; argv[2][i]!='\0'; i++)
	{
	if (isdigit(argv[2][i]) == 0 && strcmp(argv[2],"*") != 0)
	flag=0;
	}
	for (i=0; argv[3][i]!='\0'; i++)
	{
	if (isdigit(argv[3][i]) == 0 && strcmp(argv[3],"*") != 0)
	flag=0;
	}

	if (atoi(argv[1]) >=60 || atoi(argv[1]) <0 || atoi(argv[2]) >= 60 ||atoi(argv[2]) < 0
	|| atoi(argv[3]) >= 60 || atoi(argv[3]) < 0 && flag==1)
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
while (1) {
	int detikitubintang,menititubintang,jamitubintang;

	if (strcmp (argv [1], "*") == 0)
	detikitubintang =1;

	if (strcmp (argv [2], "*") == 0)
	menititubintang =1;

	if (strcmp (argv [3], "*") == 0)
	jamitubintang =1;

	int detik = atoi (argv[1]);
	int menit = atoi (argv [2]);
	int jam = atoi (argv [3]);

	time_t waktu;
	struct tm *timenow;
	time( &waktu );
	timenow = localtime( &waktu );



	int detikbenar,menitbenar,jambenar;
	if (detik == timenow->tm_sec || detikitubintang ==1 )
	detikbenar =1;
	if ( menit == timenow->tm_min || menititubintang == 1)
	menitbenar = 1;
	if (jam == timenow->tm_hour || jamitubintang ==1)
	jambenar =1;

	if (detikbenar ==1 && jambenar ==1 && menitbenar ==1)
	{
		pid_t id_child;
		id_child = fork();

		if (id_child== 0) {
		char *pathsh[] = {"bash", argv[4], NULL};
		execv("/bin/bash", pathsh);
							}
		else if (id_child <0)
		exit(EXIT_FAILURE);

	}

	sleep(1);

}
}
