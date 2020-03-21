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
#define Size 50
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <sys/time.h>

int main(int argc, char* argv) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
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
    int status,status1,status2,status3;


    time_t t ;
    struct tm *tmp ;
    char MY_TIME[Size];
    time( &t );
    tmp = localtime( &t );
      // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d_%H:%M:%S", tmp);

    //strcat supaya membuat direktori dengan timestamp
    char namafolder [] = "/home/eric/";
    strcat (namafolder,MY_TIME);

    pid_t id_child;
    id_child = fork();

    if (id_child <0)
    exit (EXIT_FAILURE);

    if (id_child == 0)
    {

      char *mkdir[] = {"mkdir", "-p", namafolder, NULL};
      execv("/bin/mkdir", mkdir);
    }


    while ((wait(&status)) > 0);
    pid_t id_child2 = fork ();

    if (id_child2 <0)
    exit (EXIT_FAILURE);


    if (id_child2 == 0)
    {

    chdir (namafolder);
    char namafolder1 [1000];
    strcpy (namafolder,namafolder1);
    int i;
    for (i=1;i<=20;i++)
      {
        // Ini semua cuma buat cari EPOCH linux time
        struct timeval tv;
        gettimeofday(&tv, NULL);
        int num = tv.tv_sec;
        num = (num %1000) +100; //download size disoal
        int length = snprintf( NULL, 0, "%d", num );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", num );
        //Epoch time ada didalam str

        //Membuat URL DOnwload
        char urldownload [] = "https://picsum.photos/";
        strcat (urldownload, str);

        //Membuat nama file yg didownload
        time_t t ;
        struct tm *tmp ;
        char namafile[Size];
        time( &t );
        tmp = localtime( &t );
        // using strftime to display time
        strftime(namafile, sizeof(namafile), "%Y-%m-%d_%H:%M:%S", tmp);


        //wget - P namafolder urldownload
        pid_t id_child3;
        id_child3 = fork ();
        if (id_child3 <0)
        exit (EXIT_FAILURE);

        if (id_child3 == 0)
        {
        char *wget[] = {"wget",urldownload,"-O",namafile, NULL};
		    execv("/usr/bin/wget",wget);
        }


       if (i == 20)
        {
          sleep (1);
          chdir("..");
          char namazip [1000];
          strcpy (namafolder1, namazip);
          strcat (namazip, ".zip");
          char *zip[] = {"zip", "-r", namazip, namafolder1, NULL};
          execv("/usr/bin/zip",zip);
        }



        sleep (5);
      }


    }

    
    while(wait(&status3) > 0);
    pid_t id_child5 = fork();
if(id_child5 < 0) exit(0);
    if(id_child5 == 0)
    {
        char *ag[] = {"rm", "-r", namafolder, NULL};
      execv("/bin/rm", ag);
    }
    
  sleep(30);
  }


  }
