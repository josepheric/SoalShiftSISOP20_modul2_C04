# SoalShiftSISOP20_modul2_C04
No 3
A.#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
 
int cfileexists(const char * filename){
  /* try to open file to read */
  FILE *file;
  if (file = fopen(filename, "r")){
      fclose(file);
      return 1;
  }
  return 0;
}
 
int main() {
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
 
if ((chdir("/home/user/modul2-2020/soal3")) < 0) {
  exit(EXIT_FAILURE);
}
 
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
 
 
while(1) {
   // main program here
   int fileno=1;
   // main program here
   FILE *file1, *file2;
   char isi[1000];
   int a;
   memset(isi, 0, 1000);
   a = cfileexists("A.txt");
   if(a==1){
       file1=fopen("A.txt","w");
       fclose(file1);
       file2=fopen("A.txt,w");
       fprintf(file2,"%s",isi);
       fclose(file2);
   }
  sleep(10);
}
 exit(EXIT_SUCCESS);
}
Open untuk membuat directory dan file tersebut
B.	FILE *destination;
	char path[PATH_MAX];
	int status;
	
	pid_t child_pid = fork();


	if(child_pid == 0)
	{
		execl("/usr/bin/unzip", "unzip", "jpg.zip", NULL);
	}

	child_pid = fork();

	if(child_pid == 0)
	{
		execl("/usr/bin/touch", "touch", "daftar.txt", NULL);
	}

	while ((wait(&status)) > 0);

	FILE *daftar = fopen("daftar.txt", "w");
	int ret = chdir("jpg");
	
	if(ret != 0) {
		perror("Error");
	}
	
	source = popen("ls *txt", "r");
	while (fgets(path, PATH_MAX, source) != NULL)
	{
		fprintf(daftar,"%s", path);
	}
	fclose(daftar); 

return 0;
}
Untuk unzip
