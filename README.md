# SoalShiftSISOP20_modul2_C04


# Penjelasan No 1

a. Program menerima 4 argumen berupa:

i. Detik: 0-59 atau * (any value)

ii. Menit: 0-59 atau * (any value)

iii. Jam: 0-23 atau * (any value)

iv. Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai

Program C untuk 1a dan 1b:
```
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

```


# Penjelasan No 3
3a) Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
```
pid_t pid2 = fork();
if(pid2 == 0) {
  char *argv[]={"mkdir","/home/dennas/modul2/indomie",NULL};
  execv("/bin/mkdir",argv);
}
else {
  sleep(5);
  char *arg2[]={"mkdir","/home/dennas/modul2/sedaap",NULL};
  execv("/bin/mkdir",arg2);
}
```
Untuk menyelesaikan soal 3a, pembuatan direktori dilakukan dengan melakukan fork() pid2. Child process akan melakukan mkdir /home/dennas/modul2/indomie, dan parent process akan melakukan mkdir /home/dennas/modul2/sedaap dalam selang waktu 5 detik.

3b) Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Dari soal 3a, maka perlu dilakukan fork() dimana child process akan melalukan soal 3a, dan parent processnya akan meng-ekstrak file jpg.zip ke direktori /home/[user]/modul2/
```
char *arg[]={"unzip","-qq","/home/dennas/modul2/jpg.zip","-d","/home/dennas/modul2",NULL};
execv("/usr/bin/unzip",arg);
unzip bash command untuk unzip file
-qq agar unzip tidak mengeluarkan outpun apapun (quiet)
/home/dennas/modul2/jpg.zip path ke file jpg.zip
-d /home/dennas/modul2 hasil unzipped file akan diletakkan ke /home/dennas/modul2
```
3c) Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.



Untuk menyelesaikan soal 3c, dimana hasil ekstrak jpg.zip yang berupa file akan dipindahkan ke /home/[USER]/modul2/sedaap/ dan yang berupa direktori akan dipindahkan ke /home/[USER]/modul2/indomie/ akan diperlukan 2 proses. Sehingga dilakukan hal seperti berikut ini.

```
pid_t pid4 = fork();
int status4;
if(pid4 == 0) {
  char *arg[]={"find","/home/dennas/modul2/jpg","-type","f","-exec","mv","{}","/home/dennas/modul2/sedaap",";",NULL};
  execv("/usr/bin/find",arg);
}
else {
  while((wait(&status4)) > 0);
  char *arg[]={"find","/home/dennas/modul2/jpg","!","-path","/home/dennas/modul2/jpg","-prune","-exec","mv","{}","/home/dennas/modul2/indomie",";",NULL};
  execv("/usr/bin/find",arg);
}
 ```
pid_t pid4 = fork();process di fork() dan int status4; untuk status process
dalam child process untuk mencari isi direktori jpg yang berbentuk file dan memindahkannya ke /home/dennas/modul2/sedaap, maka dilakukan bash command: find /home/dennas/modul2/jpg -type f -exec mv {} /home/dennas/modul2/sedaap ;
find /home/dennas/modul2/jpg command untuk mencari /home/dennas/modul2/jpg
-type f find akan mencari yang bertype file
-exec mv {} /home/dennas/modul2/sedaap ; hasil find kemudian akan dipindahkan dengan mv ke /home/dennas/modul2/sedaap
dalam parent process untuk mencari isi direktori jpg yang berbentuk direktori dan memindahkannya ke /home/dennas/modul2/indomie, maka dilakukan bash command: find /home/dennas/modul2/jpg ! -path /home/dennas/modul2/jpg -prune -exec mv {} /home/dennas/modul2/indomie ;
sebelum command dijalankan, dilakukan while((wait(&status4)) > 0); wait child process berjalan hingga selesai baru ke parent process
find /home/dennas/modul2/jpg command untuk mencari /home/dennas/modul2/jpg
! -path /home/dennas/modul2/jpg -prune kecuali path /home/dennas/modul2/jpg itu sendiri akan di -prune, yaitu untuk mencegah melakukan find ke path tersebut
-exec mv {} /home/dennas/modul2/indomie ; hasil find kemudian akan dipindahkan dengan mv ke /home/dennas/modul2/indomie
3d) Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).

untuk 3d  akan dilakukan fork() dengan soal 3c (bagian untuk memindahkan direktori) merupakan child processnya, dan soal 3d pada parent process.

Untuk menyelesaikan soal 3d, dilakukan fork() sebagai berikut:
```
pid_t pid6 = fork();
if(pid6 == 0) {
   char *arg[]={"find","/home/dennas/modul2/indomie","!","-path","/home/dennas/modul2/indomie","-prune","-exec","touch","{}/coba1.txt",";",NULL};
   	execv("/usr/bin/find",arg);
}
else {
   	sleep(3);
   	char *arg[]={"find","/home/dennas/modul2/indomie","!","-path","/home/dennas/modul2/indomie","-prune","-exec","touch","{}/coba2.txt",";",NULL}; 
   execv("/usr/bin/find",arg);
}
```
pid_t pid6 = fork();process di fork()
dalam child process akan dibuat file coba1.txt di masing-masing direktori yang ada di /home/dennas/modul2/indomie, maka dilakukan bash command: find /home/dennas/modul2/indomie ! -path /home/dennas/modul2/indomie -prune -exec touch {}/coba1.txt ;
find /home/dennas/modul2/indomie command untuk mencari /home/dennas/modul2/indomie dimana letak direktori yang akan diisi coba1.txt dan coba2.txt
-path /home/dennas/modul2/indomie -prune kecuali path /home/dennas/modul2/indomie itu sendiri akan di -prune, yaitu untuk mencegah melakukan find ke path tersebut
-exec touch {}/coba1.txt ; hasil find kemudian akan dilakukan touch atau membuat file kosong coba1.txt
dalam parent process akan dibuat file coba2.txt di masing-masing direktori yang ada di /home/dennas/modul2/indomie dalam selang waktu 3 detik setelah coba1.txt, maka dilakukan bash command: find /home/dennas/modul2/indomie ! -path /home/dennas/modul2/indomie -prune -exec touch {}/coba2.txt ; dengan sleep(3) sebelum bash dijalankan.
sebelum command dijalankan, dilakukan sleep(3); wait child process berjalan hingga selesai baru ke parent process
find /home/dennas/modul2/jpg command untuk mencari /home/dennas/modul2/jpg
! -path /home/dennas/modul2/indomie -prune kecuali path /home/dennas/modul2/indomie akan di -prune yaitu untuk mencegah melakukan find ke path tersebut
-exec touch {}/coba2.txt ; hasil find kemudian akan dilakukan touch atau membuat file kosong coba2.txt
run program:

Pada terminal, dilakukan compile soal2.c dengan gcc soal3.c -o soal3. Pastikan sudah terdapat direktori modul2 dimana sudah berisi jpg.zip.Kemudian dilakukan bash ./soal3 untuk menjalankan program.
Program kemudian akan membuat folder indomie dan sedaap. Kemudian program akan meng-unzip jpg.zip 
![image](https://user-images.githubusercontent.com/61129358/77229932-48a83780-6bc3-11ea-9533-89cf3832df90.png)

Pada folder sedaap, akan dipindahkan file-file yang ada di folder jpg hasil unzip.
 ![image](https://user-images.githubusercontent.com/61129358/77229952-64134280-6bc3-11ea-9ec5-1ccf680c30e2.png)
Dan pada folder indomie, akan dipindahkan folder-folder yang ada di folder jpg hasil unzip
Dan kemudian program akan membuat coba txt setiap 5 detik
![image](https://user-images.githubusercontent.com/61129358/77229963-755c4f00-6bc3-11ea-9e87-7267ff52ebd6.png)

 

