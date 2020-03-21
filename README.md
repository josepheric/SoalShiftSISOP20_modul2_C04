# SoalShiftSISOP20_modul2_C04


# Penjelasan No 1
Pertama-tama saya mengecek apakah input argumen yang diminta sesuai dengan permintaan soal, pada hal ini input detik, menit, jam, sesuai dengan format, dan parameter ke 4 yaitu direktori bash script dapat ditemukan. 

Berikut adalah kodenya:
```
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

```

Kemudian saya membuat program daemon, yang isinya sebagai berikut:
Pertama-tama saya mengecek apakah input detik,menit,jam merupakan bintang atau tidak.
Kemudian saya mengconvert detik menit jam ke integer menggunakan atoi

```
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
```

Terakhir apabila detik,menit,jam sekarang (pada pc) sesuai dengan inputan user ATAU detik, menit,jam merupakan bintang,
maka script dijalankan
```
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
```
Berikut saat program menjalankan isprime.sh yang isinya 
#!/bin/bash
date >> ~/date.txt

![Screenshot from 2020-03-21 22-46-31](https://user-images.githubusercontent.com/61129358/77230328-fddbef00-6bc5-11ea-99c3-845f6439fb48.png)

Beriku isi date.txt:


![Screenshot from 2020-03-21 22-49-25](https://user-images.githubusercontent.com/61129358/77230402-7fcc1800-6bc6-11ea-999a-55b5bc7997e0.png)




# Penjelasan No 2:
Untuk no 2 saya hanya dapat:
a. Membuat folder yang namanya berupa timestamp:
```
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
 ```
 b. Mendownload Gambar ke folder tersebut sebanyak 20 kali dengan cara membuat child process baru dengan fork ()
 ```

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
```
Gambar yang didownload akan memeiliki naam file berupa timestamp, dan memiliki ukuran file pesergi sebesar (epoch linux time % 1000) + 100 pixel. Gamabr akan didownload tiap 5 detik. Folder akan dibuat tiap 30 detik
Berikut adalah hasil menjalankan program diatas:

![Screenshot from 2020-03-21 22-57-18](https://user-images.githubusercontent.com/61129358/77230553-9757d080-6bc7-11ea-9606-393056cd52db.png)


![Screenshot from 2020-03-21 22-57-18](https://user-images.githubusercontent.com/61129358/77230536-7ee7b600-6bc7-11ea-9db2-d27686e1da15.png)

![Screenshot from 2020-03-21 22-57-52](https://user-images.githubusercontent.com/61129358/77230582-d0904080-6bc7-11ea-9c4b-aa92b9b2b443.png)





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

 

