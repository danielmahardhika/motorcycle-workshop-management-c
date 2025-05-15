#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//anti input huruf
char ch;
int c;

//struct untuk servis
typedef struct {
    int nomor_antrian;
    char plat_nomor[20];
    char nama_kendaraan[50];
    char merk_kendaraan[50];
    char jenis_servis[10];
    char riwayat_kerusakan[255];
} Servis;

//struck untuk part
typedef struct {
	int nomor_part;
	char jenis_part[50];
	char merk_part[50];
	int jumlah_part;
	int harga_part;
} Part;

//untuk mencatat riwayat pada riwayat.txt
void logActivity(char activity[1000]) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    FILE *fptr = fopen("riwayat.txt", "a");
    fprintf(fptr, "%02d/%02d/%04d - %02d:%02d:%02d - %s\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min, t->tm_sec, activity);
    fclose(fptr);
}

//gotoxy untuk letak agar rapi
void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

//loading
void loadingBar()
{
    system("cls");
    system("color 0E"); // ubah warna menjadi hitam dan hijau terang

    char a = 177, b = 219;
  
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t\t  \033[36mLoad\033[1;36ming...\n\n\033[32m");
    printf("\t\t\t\t\t");
  
    for (int i = 0; i < 26; i++)
        printf("%c", a);
  
    printf("\r");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++) {
        printf("%c", b);
        Sleep(30);
    }
    printf("\033[0m\n");
    system("cls");
}

//readPASS untuk membaca passwordd
void readPass(char *temp){
    int key = 0, index = 0;

    do {
        key = getch(); //simpan karakter yang ditekan ke dalam variabel key 

        switch (key) {

                /* 0 adalah kode awal untuk tombol fungsi (function key), seperti F1, F2, ..., F12
                  Misalkan jika tombol F1 ditekan, maka fungsi getch akan mengembalikan
                  nilai 0 dan menyimpan sebuah kode yang menandakan tombol F1 ditekan ke buffer.
                 */
            case 0:

                /* 224 adalah kode awal untuk tombol panah, home, page up, page down, end dan lain-lain.
                  Misalkan jika tombol panah ditekan, fungsi getch akan
                  mengembalikan nilai 224 dan menyimpan sebuah kode
                  yang menandakan tombol yang ditekan ke buffer.
                 */
            case 224:

                // fungsi getch di sini digunakan untuk membersihkan buffer 
                getch();

                break;

                // jika tombol back space ditekan, maka mundurkan cursor satu langkah 
            case '\b':
                if (index > 0) {
                    index = index - 1; // kurangi index temp sebesar 1 
                    temp[index] = 0; // set temp[index] menjadi kosong (NUL) 

                    printf("\b \b"); // mundurkan cursor satu langkah 
                }

                break;
            default:

                /* Hanya karakter printable yang dapat ditekan, seperti huruf, angka dan karakter spesial */
                if (key > 31 && key < 127) {
                    temp[index] = key; /* Simpan karakter ke dalam temp[index] */
                    index = index + 1; /* Naikkan nilai index sebesar 1 */

                    printf("*");
                }
        }

        /* 13 adalah kode ASCII untuk karakter enter.
         * Perulangan akan terus dilakukan sampai tombol enter ditekan.
         */
    } while (key != 13);

    /* Menambahkan NUL di akhir temp yang menandakan akhir dari sebuah string */
    temp[index] = '\0';
}

//Up key - 224 72
//Down key - 224 80
//Left key - 224 75
//Right key - 224 77
// ascii 219

//panah untuk menu
void arrowhere (int realposition,int arrowposition){
    if(realposition == arrowposition){
        printf("-->");
    }else{
        printf("   ");
    }
}


//main untuk login kemudian masuk ke void menu awal
int main(){
    char usrnm[6], pass[10];
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	loadingBar();
    system("cls");
    gotoxy(40,3);  printf("\033[36m+--------------------------------------+\033[0m\n");
    gotoxy(40,5);  printf("\033[33;45m       LOGIN BENGKEL WUS ORA UMUM       \033[0m\n ");
    gotoxy(40,7);  printf("\033[36m+--------------------------------------+\033[0m\n");
    gotoxy(40,9);  printf("\033[1;33mMasukkan Username (Admin)\t: ");
    gotoxy(40,10); printf("Masukkan Password\t\t: \033[0m\n");
    gotoxy(40,12); printf("\033[36m+--------------------------------------+\033[0m\n");

    gotoxy(74,9); scanf("%s",&usrnm);
    gotoxy(74,10); readPass(pass);
    if(strcmp(usrnm,"admin")==0 && strcmp(pass,"admin")==0){
	logActivity("Login berhasil");
	menuawal();
	}
    else {
        gotoxy(40,13); printf("     Username/Password Salah!!!");
        logActivity("Login gagal");
        getch();
        return main();
    }
    return 0;
}

//menu awal
void menuawal(){
    system("cls");
    printf("\e[?25l");
    int pil, c;
    //deklarasi untuk option panah
    int position = 1;
    int keyPressed = 0;
    int maxoption = 3;
    loadingBar();
    while(keyPressed != 13){
        system("COLOR 0B"); 
        gotoxy(8,3);printf("\033[36m+--------------------------------------------------------------------------------------------------------+\n\033[0m\n");
        gotoxy(50, 4);printf("\033[1;36mBENGKEL WUS ORA UMUM\033[0m\n");
        gotoxy(8,5);printf("\033[36m+--------------------------------------------------------------------------------------------------------+\n\033[0m\n");
        gotoxy(15, 6);arrowhere(1, position);printf("\033[1;33m 1.  Daftar Servis\033[0m"); 
        gotoxy(15, 8);arrowhere(2, position);printf("\033[1;33m 2.  Daftar Part\033[0m"); 
        gotoxy(15, 10);arrowhere(3, position);printf("\033[1;33m 3.  Lihat Daftar Servis\033[0m");
        gotoxy(15, 12);arrowhere(4, position);printf("\033[1;33m 4.  Lihat Daftar Part\033[0m"); 
        gotoxy(15, 14);arrowhere(5, position);printf("\033[1;33m 5.  Hapus Data Servis\033[0m"); 
        gotoxy(45, 6);arrowhere(6, position);printf("\033[1;33m 6.  Hapus Data Part\033[0m"); 
        gotoxy(45, 8);arrowhere(7, position);printf("\033[1;33m 7.  Edit Data Servis\033[0m"); 
        gotoxy(45, 10);arrowhere(8, position);printf("\033[1;33m 8.  Edit Data Part\033[0m");
        gotoxy(45, 12);arrowhere(9, position);printf("\033[1;33m 9.  Pencarian Data Servis\033[0m"); 
        gotoxy(45, 14);arrowhere(10, position);printf("\033[1;33m 10. Pencarian Data Part\033[0m"); 
        gotoxy(75, 6);arrowhere(11, position);printf("\033[1;33m 11. Sorting Data Servis\033[0m");
        gotoxy(75, 8);arrowhere(12, position);printf("\033[1;33m 12. Sorting Data Part\033[0m");
        gotoxy(75, 10);arrowhere(13, position);printf("\033[1;33m 13. Riwayat Aktifitas Bengkel\033[0m");
        gotoxy(75, 12);arrowhere(14, position);printf("\033[1;33m 14. Data Diri\033[0m"); 
        gotoxy(75, 14);arrowhere(15, position);printf("\033[1;33m 15. Exit\033[0m"); 

        keyPressed = getch();
        if(keyPressed == 80 && position != 15 ){
            position++;
        }else if(keyPressed == 72 && position != 1){
            position--;
        }else if(keyPressed == 77 && position != 11 && position != 12 && position != 13 && position != 14 && position != 15){
            position += 5;   
        }else if(keyPressed == 75 && position != 1 && position != 2 && position != 3 && position != 4 && position != 5){ 
            position -= 5;
        }
        else{
            position = position;
        }

        if (keyPressed == 13 && position == 1){
            tambah_servis();
        }else if(keyPressed == 13 && position == 2){
            tambah_part();
        }else if(keyPressed == 13 && position == 3){
            lihat_servis();
        }else if(keyPressed == 13 && position == 4){
            lihat_part();
        }else if(keyPressed == 13 && position == 5){
            hapus_servis();
        }else if(keyPressed == 13 && position == 6){
            hapus_part();
        }else if(keyPressed == 13 && position == 7){
            edit_servis();
        }else if(keyPressed == 13 && position == 8){
            edit_part();
        }else if(keyPressed == 13 && position == 9){
            searchservis();
        }else if(keyPressed == 13 && position == 10){
            searchpart();
        }else if(keyPressed == 13 && position == 11){
            sortservis();
        }else if(keyPressed == 13 && position == 12){
            sortpart();
        }else if(keyPressed == 13 && position == 13){
            riwayat();
        }else if(keyPressed == 13 && position == 14){
            datadiri();
        }else if(keyPressed == 13 && position == 15){
            loadingBar();
			system("cls");
			system("color 73");
			printf("+----------------------------------------------------------------------------------------------------------------------+");
		    gotoxy(49,1);printf("KELUAR DARI PROGRAM\n");
		    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
		    gotoxy(28,5);printf("TERIMA KASIH TELAH MENGGUNAKAN PROGRAM BENGKEL WES ORA UMUM");
		    gotoxy(40,8);printf("DANIEL SATRIA MAHARDHIKA - 672022019");
		    gotoxy(40,9);printf("YOHANES YOGI BAGAS ASMORO - 672022046");
		    gotoxy(40,10);printf("GENESY MATTHEW WIBOWO - 672022316\n\n\n\n\n\n\n\n\n\n");
		    gotoxy(36,19);printf("PROGRAM BENGKEL WUS ORA UMUM V1.0 - 2023\n");
		    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
		    logActivity("Keluar dari program");
		    exit(0);
        }
    }
}

//penambahan servis
void tambah_servis() {
    FILE *file;
    Servis servis;
    int n=0,m=0;
    m=m+n;
    loadingBar();
    system("color 73");
    system("cls");
    printf("\e[?25h");

    gotoxy(40, 8);
    printf("+--------------------------------------+");
    gotoxy(51, 9);
    printf("TAMBAH DATA SERVIS");
    gotoxy(40, 10);
    printf("+--------------------------------------+");


    file = fopen("servis.txt", "a+");
    if (!file) {
        gotoxy(40, 12);
        printf("Tidak bisa membuka file servis.txt!\n");
        return;
    }
    gotoxy(40, 12);
    printf("Input nomor antrian: ");
    while (scanf("%d", &servis.nomor_antrian) != 1) {
    	while (!isspace(c = getchar()));
		ungetc(c, stdin);
        gotoxy(40, 13+n);
        printf("Input berupa angka, coba lagi: ");
        getchar();
        n++;
    }
    getchar();
// menggunakan fgets karena lebih fleksibel untuk berbagi macam format string
    gotoxy(40, 13+n);
    printf("Input plat nomor: ");
    fgets(servis.plat_nomor, sizeof(servis.plat_nomor), stdin);
    servis.plat_nomor[strcspn(servis.plat_nomor, "\n")] = '\0';

    gotoxy(40, 14+n);
    printf("Input nama kendaraan: ");
    fgets(servis.nama_kendaraan, sizeof(servis.nama_kendaraan), stdin);
    servis.nama_kendaraan[strcspn(servis.nama_kendaraan, "\n")] = '\0';

    gotoxy(40, 15+n);
    printf("Input merk kendaraan: ");
    fgets(servis.merk_kendaraan, sizeof(servis.merk_kendaraan), stdin);
    servis.merk_kendaraan[strcspn(servis.merk_kendaraan, "\n")] = '\0';

    gotoxy(40, 16+n);
    printf("Input jenis servis (ringan/berat): ");
    while (1) {
        fgets(servis.jenis_servis, sizeof(servis.jenis_servis), stdin);
        servis.jenis_servis[strcspn(servis.jenis_servis, "\n")] = '\0';
        if (stricmp(servis.jenis_servis, "ringan") == 0 || stricmp(servis.jenis_servis, "berat") == 0) {
            break;
        }
        gotoxy(40, 17+n+m);printf("Servis tidak ada! Input jenis servis (ringan/berat): ");
        m++;
    }
    gotoxy(40, 17+n+m);
    printf("Riwayat kerusakan: ");
    fgets(servis.riwayat_kerusakan, sizeof(servis.riwayat_kerusakan), stdin);
    servis.riwayat_kerusakan[strcspn(servis.riwayat_kerusakan, "\n")] = '\0';

    fprintf(file, "%d|%s|%s|%s|%s|%s\n", servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan);
    fclose(file);
    fclose(file);

	logActivity("Menambahkan data servis");
    gotoxy(40, 19+n+m);
    printf("Data berhasil ditambahkan!\n");
	getch();
    menuawal();
}

void tambah_part(){
	FILE *file;
    Part part;
    int n=0,m=0,o=0;
    m=m+n;
    o=o+m;
	
	loadingBar();
	system("color 73");
    system("cls");
    printf("\e[?25h");

    gotoxy(40, 8);
    printf("+--------------------------------------+");
    gotoxy(52, 9);
    printf("TAMBAH DATA PART");
    gotoxy(40, 10);
    printf("+--------------------------------------+");

    file = fopen("part.txt", "a+");
    if (!file) {
        gotoxy(40, 12);
        printf("Tidak bisa membuka file part.txt!\n");
        return;
    }

    gotoxy(40, 12);
    printf("Input nomor part: ");
    while (scanf("%d", &part.nomor_part) != 1) {
    	while (!isspace(c = getchar()));
		ungetc(c, stdin);
        gotoxy(40, 13+n);
        printf("Input berupa angka. Silahkan coba lagi: ");
        getchar();
        n++;
    }
    getchar();

    gotoxy(40, 13+n);
    printf("Input jenis part: ");
    fgets(part.jenis_part, sizeof(part.jenis_part), stdin);
    part.jenis_part[strcspn(part.jenis_part, "\n")] = '\0';

    gotoxy(40, 14+n);
    printf("Input merk part: ");
    fgets(part.merk_part, sizeof(part.merk_part), stdin);
    part.merk_part[strcspn(part.merk_part, "\n")] = '\0';

    gotoxy(40, 15+n);
    printf("Input jumlah part: ");
    while (scanf("%d", &part.jumlah_part) != 1) {
    	while (!isspace(c = getchar()));
		ungetc(c, stdin);
        gotoxy(40, 16+n+m);
        printf("Input berupa angka. Silahkan coba lagi: ");
        getchar();
        m++;
    }
    getchar();

    gotoxy(40, 16+n+m+o);
    printf("Input harga part: Rp. ");
    while (scanf("%d", &part.harga_part) != 1 ) {
    	while (!isspace(c = getchar()));
		ungetc(c, stdin);
        gotoxy(40, 17+n+m+o);
        printf("Input berupa angka. Silahkan coba lagi: ");
        getchar();
        o++;
    }
    getchar();

    fprintf(file, "%d|%s|%s|%d|%d\n", part.nomor_part, part.jenis_part, part.merk_part, part.jumlah_part, part.harga_part);
    fclose(file);
    fclose(file);
    
	logActivity("Menambahkan data part");
    gotoxy(40, 18+n+m+o);
    printf("Data berhasil ditambahkan!\n");
    getch();
    menuawal();
}

void lihat_servis() {
    FILE *file;
    Servis servis;
    int nomor = 1;
    int ada_data = 0;

    file = fopen("servis.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file servis.txt!\n");
        return;
    }
	loadingBar();
	system("color 73");
    system("cls");
    gotoxy(40, 2);
    printf("BENGKEL WES ORA UMUM\n\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor Antrian\tPlat Nomor\tNama Kendaraan\t\tMerk Kendaraan\tJenis Servis\tRiwayat Kerusakan\t\t|\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]%*c", &servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan) == 6) {
        printf("   %d\t%d\t\t%s\t%s\t\t\t%s\t\t%s\t\t%s\n", nomor++, servis.nomor_antrian, strupr(servis.plat_nomor), strupr(servis.nama_kendaraan), strupr(servis.merk_kendaraan), strupr(servis.jenis_servis), strupr(servis.riwayat_kerusakan));
        ada_data = 1;
    }

    if (!ada_data) {
        printf("\n\t\t\t\t\tBelum ada input data.\n\n");

    }
     printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    fclose(file);
    logActivity("Melihat data servis");
    getch();
    menuawal();
}

void lihat_part(){
	FILE *file;
    Part part;
    int nomor = 1;
    int ada_data = 0;

    file = fopen("part.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file part.txt!\n");
        return;
    }
    loadingBar();
    system("color 73");
	system("cls");
	gotoxy(40,2);
    printf("BENGKEL WES ORA UMUM\n\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor-Part\tJenis Part\tMerk Part\tJumlah Part\tHarga Part\t\t|\n");
	printf("+-----------------------------------------------------------------------------------------------+\n");
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d", &part.nomor_part, part.jenis_part, part.merk_part, &part.jumlah_part, &part.harga_part) == 5) {
    	printf("   %d\t%d\t\t%s\t\t%s\t\t%d\t\t%d\n", nomor++, part.nomor_part, strupr(part.jenis_part), strupr(part.merk_part), part.jumlah_part, part.harga_part);
    	ada_data=1;
    }
    if (!ada_data) {
        printf("\n\t\t\t\t\tBelum ada input data.\n\n");
	}
    printf("+-----------------------------------------------------------------------------------------------+\n");
    fclose(file);
    logActivity("Melihat data part");
    getch();
    menuawal();
}

void edit_servis() {
    FILE *file, *file_temp;
    Servis servis;
    int nomor_antrian, found = 0;
    int nomor=1;
    int ada_data=0;

    file = fopen("servis.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file servis.txt!\n");
        return;
    }

    file_temp = fopen("servis_temp.txt", "w");
    if (!file_temp) {
        printf("Tidak bisa membuka file servis_temp.txt!\n");
        fclose(file);
        return;
    }
	
	loadingBar();
	system("color 73");
    system("cls");
    printf("\e[?25h");
    gotoxy(40, 2);
    printf("BENGKEL WES ORA UMUM\n\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor Antrian\tPlat Nomor\tNama Kendaraan\t\tMerk Kendaraan\tJenis Servis\tRiwayat Kerusakan\t\t|\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]%*c", &servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan) == 6) {
		printf("   %d\t%d\t\t%s\t%s\t\t\t%s\t\t%s\t\t%s\n", nomor++, servis.nomor_antrian, strupr(servis.plat_nomor), strupr(servis.nama_kendaraan), strupr(servis.merk_kendaraan), strupr(servis.jenis_servis), strupr(servis.riwayat_kerusakan));
        ada_data = 1;
    }

    if (!ada_data) {
        printf("\n\t\t\t\t\tBelum ada input data.\n\n");

    }
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    printf("Masukkan nomor antrian yang ingin diedit: ");
    while (scanf("%d", &nomor_antrian) != 1) {
	    		while (!isspace(c = getchar()));
				ungetc(c, stdin);
	        	printf("Nomor antrian harus menggunakan angka. Silahkan coba lagi: ");
	       	 	getchar();
    		}
    getchar();
	rewind(file);
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]%*c", &servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan) == 6) {
        if (servis.nomor_antrian == nomor_antrian) {
            found = 1;

            printf("Input nomor antrian: ");
    		while (scanf("%d", &servis.nomor_antrian) != 1) {
	    		while (!isspace(c = getchar()));
				ungetc(c, stdin);
	        	printf("Nomor antrian harus menggunakan angka. Silahkan coba lagi: ");
	       	 	getchar();
    		}
   			getchar();

            printf("Input plat nomor: ");
            fgets(servis.plat_nomor, sizeof(servis.plat_nomor), stdin);
            servis.plat_nomor[strcspn(servis.plat_nomor, "\n")] = '\0';

            printf("Input nama kendaraan: ");
            fgets(servis.nama_kendaraan, sizeof(servis.nama_kendaraan), stdin);
            servis.nama_kendaraan[strcspn(servis.nama_kendaraan, "\n")] = '\0';

            printf("Input merk kendaraan: ");
            fgets(servis.merk_kendaraan, sizeof(servis.merk_kendaraan), stdin);
            servis.merk_kendaraan[strcspn(servis.merk_kendaraan, "\n")] = '\0';

            printf("Input jenis servis (ringan/berat): ");
            while (1) {
                fgets(servis.jenis_servis, sizeof(servis.jenis_servis), stdin);
                servis.jenis_servis[strcspn(servis.jenis_servis, "\n")] = '\0';
                if (stricmp(servis.jenis_servis, "ringan") == 0 || stricmp(servis.jenis_servis, "berat") == 0) {
                    break;
                }
                printf("Servis tidak ada! Silahkan input ulang jenis servis (ringan/berat): ");
            }

            printf("Input riwayat kerusakan: ");
            fgets(servis.riwayat_kerusakan, sizeof(servis.riwayat_kerusakan), stdin);
            servis.riwayat_kerusakan[strcspn(servis.riwayat_kerusakan, "\n")] = '\0';
        }
        fprintf(file_temp, "%d|%s|%s|%s|%s|%s\n", servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan);
    }

    fclose(file);
    fclose(file_temp);

    remove("servis.txt");
    rename("servis_temp.txt", "servis.txt");

    if (found) {
    	logActivity("Mengedit data servis");
        printf("Data berhasil diedit!\n");
    } else {
        printf("Data dengan nomor antrian %d tidak ditemukan!\n", nomor_antrian);
    }
    getch();
    menuawal();
}

void edit_part(){
	FILE *file, *file_temp;
    Part part;
    int nomor_part, found = 0;
    int nomor=1;
    int ada_data=0;

    file = fopen("part.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file part.txt!\n");
        return;
    }

    file_temp = fopen("part_temp.txt", "w");
    if (!file_temp) {
        printf("Tidak bisa membuka file part_temp.txt!\n");
        fclose(file);
        return;
    }
	
	loadingBar();
	system("color 73");
    system("cls");
    printf("\e[?25h");
	gotoxy(40,2);
    printf("BENGKEL WES ORA UMUM\n\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor-Part\tJenis Part\tMerk Part\tJumlah Part\tHarga Part\t\t|\n");
	printf("+-----------------------------------------------------------------------------------------------+\n");
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d", &part.nomor_part, part.jenis_part, part.merk_part, &part.jumlah_part, &part.harga_part) == 5) {
    	printf("   %d\t%d\t\t%s\t\t%s\t\t%d\t\t%d\n", nomor++, part.nomor_part, strupr(part.jenis_part), strupr(part.merk_part), part.jumlah_part, part.harga_part);
    	ada_data=1;
    }
    if (!ada_data) {
        printf("\n\t\t\t\t\tBelum ada input data.\n\n");
	}
    printf("+-----------------------------------------------------------------------------------------------+\n");

    printf("Masukkan nomor part yang ingin diedit: ");
    while (scanf("%d", &nomor_part) != 1) {
	    		while (!isspace(c = getchar()));
				ungetc(c, stdin);
	        	printf("Nomor part harus menggunakan angka. Silahkan coba lagi: ");
	       	 	getchar();
    		}
    getchar();
	rewind(file);
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d", &part.nomor_part, part.jenis_part, part.merk_part, &part.jumlah_part, &part.harga_part) == 5) {
        if (part.nomor_part == nomor_part) {
            found = 1;

            printf("Input nomor part: ");
		    while (scanf("%d", &part.nomor_part) != 1) {
		    	while (!isspace(c = getchar()));
				ungetc(c, stdin);
		        printf("Nomor part harus menggunakan angka. Silahkan coba lagi: ");
		        getchar();
		    }
		    getchar();
		
		    printf("Input jenis part: ");
		    fgets(part.jenis_part, sizeof(part.jenis_part), stdin);
		    part.jenis_part[strcspn(part.jenis_part, "\n")] = '\0';
		
		    printf("Input merk part: ");
		    fgets(part.merk_part, sizeof(part.merk_part), stdin);
		    part.merk_part[strcspn(part.merk_part, "\n")] = '\0';
		
		    printf("Input jumlah part: ");
		    while (scanf("%d", &part.jumlah_part) != 1) {
		    	while (!isspace(c = getchar()));
				ungetc(c, stdin);
		        printf("Jumlah part harus menggunakan angka. Silahkan coba lagi: ");
		        getchar();
		    }
		    getchar();
		
		    printf("Input harga part: Rp. ");
		    while (scanf("%d", &part.harga_part) != 1) {
		    	while (!isspace(c = getchar()));
				ungetc(c, stdin);
		        printf("Harga part harus menggunakan angka. Silahkan coba lagi: ");
		        getchar();
		    }
		    getchar();
        }
        fprintf(file_temp, "%d|%s|%s|%d|%d\n", part.nomor_part, part.jenis_part, part.merk_part, part.jumlah_part, part.harga_part);
    }

    fclose(file);
    fclose(file_temp);

    remove("part.txt");
    rename("part_temp.txt", "part.txt");

    if (found) {
    	logActivity("Mengedit data part");
        printf("Data berhasil diedit!\n");
    } else {
        printf("Data dengan nomor part %d tidak ditemukan!\n", nomor_part);
    }
    getch();
    menuawal();
}

void hapus_servis() {
    FILE *file, *file_temp;
    Servis servis;
    int nomor_antrian, found = 0;
    int ada_data=0;
    int nomor=1;

    file = fopen("servis.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file servis.txt!\n");
        return;
    }

    file_temp = fopen("servis_temp.txt", "w");
    if (!file_temp) {
        printf("Tidak bisa membuka file servis_temp.txt!\n");
        fclose(file);
        return;
    }
    loadingBar();
    system("color 73");
    system("cls");
    printf("\e[?25h");
    gotoxy(40, 2);
    printf("BENGKEL WES ORA UMUM\n\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor Antrian\tPlat Nomor\tNama Kendaraan\t\tMerk Kendaraan\tJenis Servis\tRiwayat Kerusakan\t\t|\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]%*c", &servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan) == 6) {
		printf("   %d\t%d\t\t%s\t%s\t\t\t%s\t\t%s\t\t%s\n", nomor++, servis.nomor_antrian, strupr(servis.plat_nomor), strupr(servis.nama_kendaraan), strupr(servis.merk_kendaraan), strupr(servis.jenis_servis), strupr(servis.riwayat_kerusakan));
        ada_data = 1;
    }

    if (!ada_data) {
        printf("\n\t\t\t\t\tBelum ada input data.\n\n");

    }
     printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    printf("Masukkan nomor antrian servis yang mau dihapus: ");
    while (scanf("%d", &nomor_antrian) != 1) {
	    		while (!isspace(c = getchar()));
				ungetc(c, stdin);
	        	printf("Nomor antrian harus menggunakan angka. Silahkan coba lagi: ");
	       	 	getchar();
    		}
    getchar();
	rewind(file);
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]%*c", &servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan) == 6) {
        if (servis.nomor_antrian == nomor_antrian) {
            found = 1;
        } else {
            fprintf(file_temp, "%d|%s|%s|%s|%s|%s\n", servis.nomor_antrian, servis.plat_nomor, servis.nama_kendaraan, servis.merk_kendaraan, servis.jenis_servis, servis.riwayat_kerusakan);
        }
    }

    fclose(file);
    fclose(file_temp);

    remove("servis.txt");
    rename("servis_temp.txt", "servis.txt");

    if (found) {
    	logActivity("Menghapus data servis");
        printf("Data berhasil dihapus!\n");
    } else {
        printf("Data dengan nomor antrian %d tidak ditemukan!\n", nomor_antrian);
    }
    getch();
    menuawal();
}

void hapus_part(){
	FILE *file, *file_temp;
    Part part;
    int nomor_part, found = 0;
    int nomor=1;
    int ada_data=0;

    file = fopen("part.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file part.txt!\n");
        return;
    }

    file_temp = fopen("part_temp.txt", "w");
    if (!file_temp) {
        printf("Tidak bisa membuka file part_temp.txt!\n");
        fclose(file);
        return;
    }
    loadingBar();
    system("color 73");
    system("cls");
    printf("\e[?25h");
	gotoxy(40,2);
    printf("BENGKEL WES ORA UMUM\n\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor-Part\tJenis Part\tMerk Part\tJumlah Part\tHarga Part\t\t|\n");
	printf("+-----------------------------------------------------------------------------------------------+\n");
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d", &part.nomor_part, part.jenis_part, part.merk_part, &part.jumlah_part, &part.harga_part) == 5) {
    	printf("   %d\t%d\t\t%s\t\t%s\t\t%d\t\t%d\n", nomor++, part.nomor_part, strupr(part.jenis_part), strupr(part.merk_part), part.jumlah_part, part.harga_part);
    	ada_data=1;
    }
    if (!ada_data) {
        printf("\n\t\t\t\t\tBelum ada input data.\n\n");
	}
    printf("+-----------------------------------------------------------------------------------------------+\n");

    printf("Masukkan nomor part yang mau dihapus: ");
    while (scanf("%d", &nomor_part) != 1) {
	    		while (!isspace(c = getchar()));
				ungetc(c, stdin);
	        	printf("Nomor part harus menggunakan angka. Silahkan coba lagi: ");
	       	 	getchar();
    		}
    getchar();
	rewind(file);
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d", &part.nomor_part, part.jenis_part, part.merk_part, &part.jumlah_part, &part.harga_part) == 5) {
        if (part.nomor_part == nomor_part) {
            found = 1;
        } else {
            fprintf(file_temp, "%d|%s|%s|%d|%d\n", part.nomor_part, part.jenis_part, part.merk_part, part.jumlah_part, part.harga_part);
        }
    }

    fclose(file);
    fclose(file_temp);

    remove("part.txt");
    rename("part_temp.txt", "part.txt");

    if (found) {
    	logActivity("Menghapus data part");
        printf("Data berhasil dihapus!\n");
    } else {
        printf("Data dengan nomor part %d tidak ditemukan!\n", nomor_part);
    }
    getch();
    menuawal();
}

void searchservis() {
    FILE *file;
    Servis servis;
    int pilihan, found = 0;
    char keyword[50];
    char line[256];
    int data_ditemukan = 0;
    int nomor=1;

    file = fopen("servis.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file servis.txt!\n");
        menuawal();
    }
    loadingBar();
	system("color 73");
	system("cls");
	printf("\e[?25h");
    gotoxy(35, 9);
	printf("+----------------------------------+");
    gotoxy(44, 10);
    printf("BENGKEL WUS ORA UMUM");
    gotoxy(35, 11);
    printf("+----------------------------------+");
    gotoxy(40, 12);
    printf("CARI DATA MELALUI:");
    gotoxy(40, 13);printf(" 1. Nomor Antrian");
    gotoxy(40, 14);printf(" 2. Nomor Plat");
    gotoxy(40, 15);printf(" 3. Nama Kendaraan");
    gotoxy(40, 16);printf(" 4. Merk Kendaraan");
    gotoxy(40, 17);printf(" 5. Jenis Servis");
    gotoxy(40, 18);printf(" 6. Riwayat Kerusakan");
    gotoxy(40, 19);printf(" 7. Keluar");
    gotoxy(40, 20);printf("Pilihan: ");
    while (scanf("%d",&pilihan) != 1) {
				    while (!isspace(c = getchar()));
				    ungetc(c, stdin);
				    system("cls");
				    gotoxy(40,15);printf("Pilihan tidak ada!");
    				getch();
				    searchservis();
				}
	if(pilihan==7){
		menuawal();
	}
	if(pilihan>7){
		system("cls");
		gotoxy(40,15);printf("Pilihan tidak valid!");
    	getch();
		searchservis();
	}
    gotoxy(40, 21);printf("Masukkan keyword: ");
    scanf(" %[^\n]", keyword);
    
    system("cls");
    gotoxy(43,1);printf("Hasil Pencarian:\n\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor Antrian\tPlat Nomor\tNama Kendaraan\t\tMerk Kendaraan\tJenis Servis\tRiwayat Kerusakan\t\t|\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
//tok dan strtok untuk memisahkan karakter dengan |

    while (fgets(line, sizeof(line), file)) {
        char *tok = strtok(line, "|");
        servis.nomor_antrian = atoi(tok);

        tok = strtok(NULL, "|");
        strcpy(servis.plat_nomor, tok);

        tok = strtok(NULL, "|");
        strcpy(servis.nama_kendaraan, tok);

        tok = strtok(NULL, "|");
        strcpy(servis.merk_kendaraan, tok);

        tok = strtok(NULL, "|");
        strcpy(servis.jenis_servis, tok);

        tok = strtok(NULL, "\n");
        strcpy(servis.riwayat_kerusakan, tok);


        //navigasi menu
        
        
        switch (pilihan) {
            case 1:
                if (servis.nomor_antrian == atoi(keyword)) {
                    found = 1;
                }
                break;
            case 2:
                if (stricmp(servis.plat_nomor, keyword) == 0) {
                    found = 1;
                }
                break;
            case 3:
                if (stricmp(servis.nama_kendaraan, keyword) == 0) {
                    found = 1;
                }
                break;
            case 4:
                if (stricmp(servis.merk_kendaraan, keyword) == 0) {
                    found = 1;
                }
                break;
            case 5:
                if (stricmp(servis.jenis_servis, keyword) == 0) {
                    found = 1;
                }
                break;
            case 6:
  				if (stricmp(servis.riwayat_kerusakan, keyword) == 0) {
        			found = 1;
    			}
   		 		break;
            default:
                printf("\t\t\t\t\tPilihan tidak valid!\n");
                break;
        }

        if (found) {
			printf("   %d\t%d\t\t%s\t%s\t\t\t%s\t\t%s\t\t%s\n", nomor++, servis.nomor_antrian, strupr(servis.plat_nomor), strupr(servis.nama_kendaraan), strupr(servis.merk_kendaraan), strupr(servis.jenis_servis), strupr(servis.riwayat_kerusakan));
            data_ditemukan = 1;
            logActivity("Searching data servis");
            found = 0;
        }
    }

    if (!data_ditemukan) {
        printf("\t\t\t\t\tData tidak ditemukan!\n");
    }
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    fclose(file);
    getch();
    menuawal();
}

void searchpart(){
	FILE *file;
    Part part;
    int pilihan, found = 0;
    char keyword[50];
    char line[256];
    int data_ditemukan = 0;
    int nomor=1;

    file = fopen("part.txt", "r");
    if (!file) {
        printf("Tidak bisa membuka file part.txt!\n");
        return;
    }
    loadingBar();
    system("color 73");
	system("cls");
	printf("\e[?25h");
    gotoxy(35, 9);
	printf("+----------------------------------+");
    gotoxy(44, 10);
    printf("BENGKEL WUS ORA UMUM");
    gotoxy(35, 11);
    printf("+----------------------------------+");
    gotoxy(40, 12);
    printf("CARI DATA MELALUI:");
    gotoxy(40, 13);printf(" 1. Nomor Part");
    gotoxy(40, 14);printf(" 2. Jenis Part");
    gotoxy(40, 15);printf(" 3. Merk Part");
    gotoxy(40, 16);printf(" 4. Jumlah Part");
    gotoxy(40, 17);printf(" 5. Harga Part");
    gotoxy(40, 18);printf(" 6. Keluar");
    gotoxy(40, 19);printf("Pilihan: ");
    while (scanf("%d",&pilihan) != 1) {
				    while (!isspace(c = getchar()));
				    ungetc(c, stdin);
				    system("cls");
				    gotoxy(40,15);printf("Pilihan tidak ada!");
    				getch();
				    searchpart();
				}
	if(pilihan==6){
		menuawal();
	}
	if(pilihan>6){
		system("cls");
		gotoxy(40,15);printf("Pilihan tidak ada!");
    	getch();
		searchpart();
	}
    gotoxy(40, 20);printf("Masukkan keyword: ");
    scanf(" %[^\n]", keyword);

	system("cls");
    gotoxy(43,1);printf("Hasil Pencarian:\n\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor-Part\tJenis Part\tMerk Part\tJumlah Part\tHarga Part\t\t|\n");
	printf("+-----------------------------------------------------------------------------------------------+\n");

    while (fgets(line, sizeof(line), file)) {
        char *tok = strtok(line, "|");
        part.nomor_part = atoi(tok);

        tok = strtok(NULL, "|");
        strcpy(part.jenis_part, tok);

        tok = strtok(NULL, "|");
        strcpy(part.merk_part, tok);
		
		tok = strtok(NULL, "|");
        part.jumlah_part = atoi(tok);
		
		tok = strtok(NULL, "|");
        part.harga_part = atoi(tok);

        //navigasi menu

        switch (pilihan) {
            case 1:
                if (part.nomor_part == atoi(keyword)) {
                    found = 1;
                }
                break;
            case 2:
                if (stricmp(part.jenis_part, keyword) == 0) {
                    found = 1;
                }
                break;
            case 3:
                if (stricmp(part.merk_part, keyword) == 0) {
                    found = 1;
                }
                break;
            case 4:
                if (part.jumlah_part == atoi(keyword)) {
                    found = 1;
                }
                break;
            case 5:
                if (part.harga_part == atoi(keyword)) {
                    found = 1;
                }
                break;
            default:
                printf("\t\t\t\t\tPilihan tidak valid!\n");
                break;
        }

        if (found) {
            printf("   %d\t%d\t\t%s\t\t%s\t\t%d\t\t%d\n", nomor++, part.nomor_part, strupr(part.jenis_part), strupr(part.merk_part), part.jumlah_part, part.harga_part);
            data_ditemukan = 1;
            logActivity("Searching data part");
            found = 0;
        }
    }

    if (!data_ditemukan) {
        printf("\t\t\t\t\tData tidak ditemukan!\n");
    }
	printf("+-----------------------------------------------------------------------------------------------+\n");
    fclose(file);
    getch();
    menuawal();
}

int compare(const void* a, const void* b, int choice, int order);
void sortservis();
void printServis(Servis* servis_array, int num_servis);

void qsort_r(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, int, int), int *choice, int *order) {
    if (nmemb <= 1) {
        return;
    }

    char *pivot = (char *) base + size * (nmemb / 2);
    char *left = (char *) base;
    char *right = (char *) base + size * (nmemb - 1);

    while (left <= right) {
        while (compar(left, pivot, *choice, *order) < 0) {
            left += size;
        }
        while (compar(right, pivot, *choice, *order) > 0) {
            right -= size;
        }
        if (left <= right) {
            char tmp[size];
            memcpy(tmp, left, size);
            memcpy(left, right, size);
            memcpy(right, tmp, size);
            left += size;
            right -= size;
        }
    }

    qsort_r(base, (right - (char *) base) / size + 1, size, compar, choice, order);
    qsort_r(left, nmemb - (left - (char *) base) / size, size, compar, choice, order);
}

void sortservis() {
    FILE *fptr;
    Servis servis_list[100];
    int i = 0, choice, order;

    fptr = fopen("servis.txt", "r");
    if (fptr == NULL) {
        printf("File tidak dapat dibuka.\n");
        return;
    }

    while (fscanf(fptr, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]%*c", &servis_list[i].nomor_antrian, servis_list[i].plat_nomor, servis_list[i].nama_kendaraan, servis_list[i].merk_kendaraan, servis_list[i].jenis_servis, servis_list[i].riwayat_kerusakan) != EOF) {
        i++;
    }
    fclose(fptr);

    int num_servis = i;

	loadingBar();
	system("color 73");
	system("cls");
	printf("\e[?25h");
   	gotoxy(35, 9);
	printf("+----------------------------------+");
    gotoxy(44, 10);
    printf("BENGKEL WUS ORA UMUM");
    gotoxy(35, 11);
    printf("+----------------------------------+\n");
    gotoxy(40, 12);printf("URUTKAN DATA MELALUI:");
    gotoxy(40, 13);printf("1. Nomor antrian");
    gotoxy(40, 14);printf("2. Nomor plat");
    gotoxy(40, 15);printf("3. Nama kendaraan");
    gotoxy(40, 16);printf("4. Merk kendaraan");
    gotoxy(40, 17);printf("5. Jenis servis");
    gotoxy(40, 18);printf("6. Riwayat kerusakan");
    gotoxy(40, 19);printf("7. Keluar");
    gotoxy(40, 20);printf("Masukkan pilihan: ");
    while (scanf("%d",&choice) != 1) {
				    while (!isspace(c = getchar()));
				    ungetc(c, stdin);
				    system("cls");
				    gotoxy(40,15);printf("Pilihan tidak ada!");
    				getch();
				    sortservis();
			}
	if(choice==7){
		menuawal();
	}
    if(choice>7){
    	system("cls");
    	gotoxy(40,15);printf("Pilihan tidak ada!");
    	getch();
    	sortservis();
	}

	
    system("cls");
   	gotoxy(35, 9);
	printf("+----------------------------------+");
    gotoxy(44, 10);
    printf("BENGKEL WUS ORA UMUM");
    gotoxy(35, 11);
    printf("+----------------------------------+\n");
    gotoxy(40, 12);printf("URUTKAN SECARA:\n");
    gotoxy(40, 13);printf("1. ASCENDING (Awal ke Akhir)\n");
    gotoxy(40, 14);printf("2. DESCENDING (Akhir ke Awal)\n");
    gotoxy(40, 15);printf("Masukkan pilihan: ");
	while (scanf("%d",&order) != 1) {
				    while (!isspace(c = getchar()));
				    ungetc(c, stdin);
				    system("cls");
				    gotoxy(40,15);printf("Pilihan tidak ada!");
    				getch();
				    sortservis();
			}
	if(order>2){
		system("cls");
    	gotoxy(40,15);printf("Pilihan tidak ada!");
    	getch();
    	sortservis();
	}

    qsort_r(servis_list, num_servis, sizeof(Servis), compare, &choice, &order);

    printServis(servis_list, num_servis);

    printf("\nTekan key untuk kembali ke menu.\n");
    logActivity("Sorting data servis");
    getch();
    menuawal();
}

//compare membandingkan dua objek Servis berdasarkan kriteria dan urutan yang ditentukan. 
//Digunakan pada fungsi pengurutan data seperti qsort.
int compare(const void* a, const void* b, int choice, int order) {
    Servis* servis_a = (Servis*) a;
    Servis* servis_b = (Servis*) b;
    int result;

    switch (choice) {
        case 1:
            result = servis_a->nomor_antrian - servis_b->nomor_antrian;

            break;
        case 2:
            result = stricmp(servis_a->plat_nomor, servis_b->plat_nomor);
            break;
        case 3:
            result = stricmp(servis_a->nama_kendaraan, servis_b->nama_kendaraan);
            break;
        case 4:
            result = stricmp(servis_a->merk_kendaraan, servis_b->merk_kendaraan);
            break;
        case 5:
            result = stricmp(servis_a->jenis_servis, servis_b->jenis_servis);
            break;
        case 6:
            result = stricmp(servis_a->riwayat_kerusakan, servis_b->riwayat_kerusakan);
            break;
        default:
            result = 0;
    }
	//descending
    if (order == 2) {
        result = -result;
    }

    return result;
}

void printServis(Servis* servis_array, int num_servis) {
	system("cls");
    gotoxy(40,1);printf("Data Servis :\n\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor Antrian\tPlat Nomor\tNama Kendaraan\t\tMerk Kendaraan\tJenis Servis\tRiwayat Kerusakan\t\t|\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < num_servis; i++) {
		printf("   %d\t%d\t\t%s\t%s\t\t\t%s\t\t%s\t\t%s\n", i+1, servis_array[i].nomor_antrian, strupr(servis_array[i].plat_nomor), strupr(servis_array[i].nama_kendaraan), strupr(servis_array[i].merk_kendaraan), strupr(servis_array[i].jenis_servis), strupr(servis_array[i].riwayat_kerusakan));
    }
}

int comparePart(const void* a, const void* b, int choice, int order) {
    Part* part_a = (Part*) a;
    Part* part_b = (Part*) b;
    int result;

    switch (choice) {
        case 1:
            result = part_a->nomor_part - part_b->nomor_part;
            break;
        case 2:
            result = stricmp(part_a->jenis_part, part_b->jenis_part);
            break;
        case 3:
            result = stricmp(part_a->merk_part, part_b->merk_part);
            break;
        case 4:
            result = part_a->jumlah_part - part_b->jumlah_part;
            break;
        case 5:
            result = part_a->harga_part - part_b->harga_part;
            break;
        default:
            result = 0;
    }

    if (order == 2) {
        result = -result;
    }

    return result;
}

void sortpart() {
    FILE *fptr;
    Part part_list[100];
    int i = 0, choice, order;

    fptr = fopen("part.txt", "r");
    if (fptr == NULL) {
        printf("File tidak dapat dibuka.\n");
        return;
    }

    while (fscanf(fptr, "%d|%[^|]|%[^|]|%d|%d", &part_list[i].nomor_part, part_list[i].jenis_part, part_list[i].merk_part, &part_list[i].jumlah_part, &part_list[i].harga_part) != EOF) {
        i++;
    }
    fclose(fptr);

    int num_part = i;
	
	loadingBar();
	system("color 73");
    system("cls");
    printf("\e[?25h");
   	gotoxy(35, 9);
	printf("+----------------------------------+");
    gotoxy(44, 10);
    printf("BENGKEL WUS ORA UMUM");
    gotoxy(35, 11);
    printf("+----------------------------------+\n");
    gotoxy(40, 12);printf("URUTKAN DATA MELALUI:");
    gotoxy(40, 13);printf("1. Nomor part\n");
    gotoxy(40, 14);printf("2. Jenis Part\n");
    gotoxy(40, 15);printf("3. Merk Part\n");
    gotoxy(40, 16);printf("4. Jumlah Part\n");
    gotoxy(40, 17);printf("5. Harga Part\n");
    gotoxy(40, 18);printf("6. Kembali\n");
    gotoxy(40, 19);printf("Masukkan pilihan: ");
    while (scanf("%d",&choice) != 1) {
				    while (!isspace(c = getchar()));
				    ungetc(c, stdin);
				    system("cls");
				    gotoxy(40,15);printf("Pilihan tidak ada!");
    				getch();
				    sortpart();
				}
	if(choice==6){
		menuawal();
	}
    if(choice>6){
    	system("cls");
    	gotoxy(40,15);printf("Pilihan tidak ada!");
    	getch();
    	sortpart();
	}

    system("cls");
   	gotoxy(35, 9);
	printf("+----------------------------------+");
    gotoxy(44, 10);
    printf("BENGKEL WUS ORA UMUM");
    gotoxy(35, 11);
    printf("+----------------------------------+\n");
    gotoxy(40, 12);printf("URUTKAN SECARA:\n");
    gotoxy(40, 13);printf("1. ASCENDING (awal ke akhir)\n");
    gotoxy(40, 14);printf("2. DESCENDING (akhir ke awal)\n");
    gotoxy(40, 15);printf("Masukkan pilihan: ");
    while (scanf("%d",&order) != 1) {
				    while (!isspace(c = getchar()));
				    ungetc(c, stdin);
				    system("cls");
				    gotoxy(40,15);printf("Pilihan tidak ada!");
    				getch();
				    sortpart();
			}
	if(order>2){
		system("cls");
    	gotoxy(40,15);printf("Pilihan tidak ada!");
    	getch();
    	sortpart();
	}

    qsort_r(part_list, num_part, sizeof(Part), comparePart, &choice, &order);

    printPart(part_list, num_part);

    printf("\nTekan key untuk kembali ke menu.\n");
    logActivity("Sorting data part");
    getch();
    menuawal();
}

void printPart(Part* part_array, int num_part) {
	system("cls");
    gotoxy(43, 1);printf("Data Part:\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("|  No\tNomor-Part\tJenis Part\tMerk Part\tJumlah Part\tHarga Part\t\t|\n");
	printf("+-----------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < num_part; i++) {
        printf("   %d\t%d\t\t%s\t\t%s\t\t%d\t\t%d\n", i+1, part_array[i].nomor_part, strupr(part_array[i].jenis_part), strupr(part_array[i].merk_part), part_array[i].jumlah_part, part_array[i].harga_part);
    }
}

void riwayat(){
	FILE *fptr = fopen("riwayat.txt", "r");

    if (fptr == NULL) {
        printf("File riwayat.txt tidak dapat dibuka.\n");
        return 0;
    }

    char line[100];
	loadingBar();
	system("color 73");
	system("cls");
    gotoxy(45,1);printf("RIWAYAT AKTIFITAS PROGRAM\n\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("  TANGGAL  -   WAKTU  - AKTIFITAS\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    while (fgets(line, sizeof(line), fptr) != NULL) {
        printf("%s", line);
    }
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    fclose(fptr);
    logActivity("Membuka riwayat aktifitas program");
    getch();
    menuawal();
    
}

void datadiri(){
	loadingBar();
	system("cls");
	system("color 73");
	printf("+----------------------------------------------------------------------------------------------------------------------+");
    gotoxy(46,1);printf("DATA PEMBUAT PROGRAM\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    gotoxy(40,8);printf("DANIEL SATRIA MAHARDHIKA - 672022019");
    gotoxy(40,9);printf("YOHANES YOGI BAGAS ASMORO - 672022046");
    gotoxy(40,10);printf("GENESY MATTHEW WIBOWO - 672022316\n\n\n\n\n\n\n\n\n\n");
    gotoxy(40,19);printf("PROGRAM BENGKEL WUS ORA UMUM V1.0 - 2023\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    logActivity("Membuka data pembuat program");
    getch();
    menuawal();
}

