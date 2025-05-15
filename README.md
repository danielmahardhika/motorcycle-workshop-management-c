Motorcycle Workshop Management
This program is a motorcycle workshop management application written in C. It utilizes data structures to store and manage service and part data for vehicles. Below is an explanation of the features and data structures used.

Key Features:
1. Login: User authentication using a username and password.
2. Service Management:
  - Add service
  - View service list
  - Edit and delete service data
  - Search service data
  - Sort service data
3. Part Management:
  - Add part
  - View part list
  - Edit and delete part data
  - Search part data
  - Sort part data
4. Activity Log: Records all activities performed within the program.
5. Developer Info: Displays information about the developers of the program.

Data Structures
The program uses two main data structures:

1. Servis Structure:
   typedef struct {
    int nomor_antrian;
    char plat_nomor[20];
    char nama_kendaraan[50];
    char merk_kendaraan[50];
    char jenis_servis[10];
    char riwayat_kerusakan[255];
} Servis;

2. Part Structure:
   typedef struct {
    int nomor_part;
    char jenis_part[50];
    char merk_part[50];
    int jumlah_part;
    int harga_part;
} Part;

Algorithms and Logic
- Search: Uses linear search to find data based on the selected criteria.
- Sorting: Utilizes qsort to sort service and part data based on user-defined criteria.
- Input Validation: Ensures that user input is valid and in the expected format.


