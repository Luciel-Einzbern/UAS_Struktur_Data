A.	Penerapan Struktur Data:
1. Pointer
Digunakan untuk variabel-variabel penunjuk seperti *next pada NodePemain, QueueJadwal, dan StackRiwayat; *left dan *right pada BSTTim; serta array dari pointer Klub* klasemen[totalKlub].
Alasan digunakan: Karena pointer digunakan untuk menunjukkan alamat data, sehingga alih-alih memindahkan atau menyalin data klub/pemain berkali-kali, program cukup memegang alamatnya saja. Ini membuat program bekerja jauh lebih ringan dan cepat.
2. Array
Digunakan untuk menyimpan daftar klasemen utama (klasemen[totalKlub]), ranking daftar pemain (rankPemain[totalPemain]), dan tabel histori head-to-head (adjMatrix di dalam Graph).
Alasan digunakan: Karena kita sudah tahu batas maksimal jumlah tim atau pemain sejak awal, kita bisa langsung menaruh dan mengambil data di nomor indeks tertentu secara instan.
3. Struct
Digunakan untuk "mapping" pembentuk objek seperti NodePemain, Klub, StatistikPemain, QueueJadwal, StackRiwayat, BSTTim, dan GraphGroup.
Alasan digunakan: Struct ini seperti "map atau formulir pendaftaran". Daripada data nama (teks) dan data poin (angka) dideklarasikan secara individual (array) untuk setiap klub, struct membungkus semuanya menjadi satu kesatuan. Sehingga kita memanggil "Klub A", semua data miliknya sudah sepaket terbawa.
4. Linked List
Digunakan untuk membuat daftar pemain (roster) di dalam suatu klub (NodePemain* rosterTim).
Alasan digunakan: Seperti "gerbong kereta api", kita bebas menyambungkan pemain baru atau melepasnya kapan saja, tanpa harus membongkar keseluruhan rangkaian data.
5. Stack
Digunakan untuk menyimpan riwayat hasil pertandingan (StackRiwayat dengan pointer topStack).
Alasan digunakan: Pertandingan yang paling baru selesai ditaruh di tumpukan paling atas. Jadi saat kita mau melihat riwayat terbaru, kita pasti langsung melihat yang paling atas dulu.
6. Queue
Digunakan untuk mengatur jadwal pertandingan yang akan datang (QueueJadwal dengan pointer frontQueue dan rearQueue).
Alasan digunakan: Sangat cocok diimplementasikan dalam penjadwalan. Kali ini digunakan menggunakan konsep FIFO (First-In - First-Out).
7. Tree
Digunakan untuk menyimpan dan mencari data Klub berdasarkan ID secara struktural (BSTTim dengan pointer rootKlub).
Alasan digunakan: Seperti "mencari kata di kamus". Kalau kita cari huruf 'M', kita bisa langsung membuka tengah buku dan mengabaikan bagian A-L. Sistem ini membuat proses pencarian ID tim menjadi sangat super cepat meski datanya sangat banyak.
8. Graph
Digunakan untuk mencatat dan memetakan klub mana yang sudah pernah bertanding melawan klub mana (GraphGroup historiGraph).
Alasan digunakan: Dengan menambahkan sesuatu seperti "garis hubungan" antar Tim A dan Tim B, berarti mereka sudah pernah bertanding. Sehingga merupakan cara paling mudah untuk melihat tim mana saja yang punya koneksi/riwayat pertemuan.
9. Sorting
Digunakan untuk fungsi urutkanKlasemen() untuk menyusun tim berdasarkan poin, dan fungsi tampilkanRankPemain() untuk menyusun pemain berdasarkan goal.
Alasan digunakan: Untuk mempermudah mencari tim mana yang juara/pemain individual mana dengan poin goal/assist tertinggi. Sorting akan otomatis membariskan tim atau pemain dari poin tertinggi hingga terendah, membuat sebuah papan skor (leaderboard).
10. Searching
Digunakan untuk fungsi cariTimDiKlasemen() untuk mencari nama klub, fungsi searchBST() untuk mencari ID tim, dan pencarian saat mengupdate gol pemain.
Alasan digunakan: Agar saat pengguna mengetik nama klub atau nama pemain, program bisa langsung menemukan datanya dengan cepat tanpa meminta pengguna melihat keseluruhan isi klasemen.


B.	Source Code:
1 - 3: Header & std.

1.	Deklarasi Struct & Pointer.
8 - 15: Deklarasi struct NodePemain (Single Linked List) untuk menyimpan roster dalam suatu Klub. Dengan field: namaPemain & posisi: string, nomorPunggung, goal & assist: integer.
17 - 23: Deklarasi struct Klub (Single Linked List) untuk menyimpan Klub Sepak Bola. Dengan field: namaKlub & asalNegara: string, id & poin: integer.
25 - 30: Deklarasi struct StatistikPemain untuk menyimpan statistik pemain individual. Dengan field: namaPemain & namaKlub: string, goal & assist: integer.
32 - 36: Deklarasi struct QueueJadwal (Single Linked List) untuk menyimpan jadwal pertandingan. Dengan field: idTim1 & idTim2: integer.
38 - 44: Deklarasi struct StackRiwayat untuk menyimpan riwayat pertandingan antar tim. Dengan field: namaTim1 & namaTim2: string, skorTim1 & skorTim2: integer.
46 - 50: Deklarasi struct BSTTim (Tree) untuk menyimpan node dalam struktur inary Search Tree berdasarkan ID klub.
52 - 54: Deklarasi struct GraphGroup untuk menyimpan histori pertemuan antar klub menggunakan Adjacency Matrix array 2 Dimensi berukuran 10x10.
56 - 57: Deklarasi static array pointer Klub untuk menyimpan semua Klub di klasemen.
59 - 60: Deklarasi static array pointer StatistikPemain untuk menyimpan semua Pemain pencetak goal/assist.
62 - 63: Inisialisasi front dan rear Queue Jadwal.
65: Inisialisasi stack Riwayat Pertandingan.
67: Inisialisasi root dari BST.
69: Inisialisasi objek historiGraph dari struct Graph.
2.	Deklarasi dan Inisialisasi Function
71 - 89: Deklarasi fungsi tambahPemain untuk menambahkan data pemain (node baru) ke akhir urutan Single Linked List di dalam suatu klub.
72 - 78: Inisialisasi node pemain baru serta mengisi informasi milik pemain.
80 - 88: Kondisi jika belum mencapai ujung linked list , maka program akan melakukan traversal ke node paling akhir, lalu menaruh node pemain baru tersebut di ujung antrean (Tail).
91 - 102: Deklarasi fungsi insert node Tree.
92 - 101: Kondisi jika Tree belum dibuat, maka inisialisasi root Tree BST. Jika tidak, jika ID klub yang input lebih kecil dari ID pada root maka pindah ke parent/daun kiri (rekursi), sebaliknya maka pindah ke kanan (rekursi).
104 - 115: Deklarasi fungsi pointer Klub untuk search berdasarkan ID Klub metode BST.
105 - 114: Kondisi jika ID klub pada root sama dengan yang dicari maka langsung keluar. Jika tidak, jika ID klub yang dicari lebih kecil dari ID pada root maka pindah ke parent/daun kiri (rekursi), sebaliknya maka pindah ke kanan (rekursi).
117 - 129: Fungsi memasukkan data ke Queue.
118 - 121: Inisialisasi node jadwal pertandingan baru serta mengisi ID milik tim yang bertanding.
123 - 128: Kondisi jika jadwal masih kosong, maka membuat Queue berdasarkan pertandingan tersebut. Jika tidak maka antrean baru diletakkan di akhir, lalu pointer rearQueue digeser ke node yang baru tersebut.
131 - 146: Fungsi boolean dequeue digunakan untuk mengeluarkan jadwal pertandingan terdepan dari Queue. Mengembalikan nilai true jika berhasil, false jika queue kosong.
136 - 138: Inisialisasi pengambilan nilai ID tim dari posisi terdepan antrean (frontQueue), kemudian menggeser frontQueue ke node berikutnya untuk menghapus antrean lama.
140 - 145: Mengecek apakah setelah digeser Queue menjadi kosong. Jika ya, rearQueue di-set menjadi NULL. Kemudian memori antrean lama dihapus dan return true.
148 - 156: Fungsi menambahkan node pada stack riwayat pertandingan.
149 - 153: Membuat node dari riwayat pertandingan terbaru.
154 - 155: Mengatur pointer next dari riwayat baru menunjuk ke riwayat lama (topStack), kemudian menjadikan riwayat baru sebagai pucuk (top) dari tumpukan data.
158 - 170: Fungsi untuk menampilkan riwayat pertandingan (stack) dari yang terbaru ke terlama.
172 - 182: Fungsi pengurutan klasemen (Bubble Sort) untuk mengurutkan tim berdasarkan poin pertandingan.
184 - 210: Fungsi mencari tim dari klasemen (Linear Search) kemudian menampilkan Informasi Klub, Roster, dan Statistik Pemain.
212 - 259: Fungsi mengupdate statistik pemain individual.
215 - 233: Melakukan pencarian linier di dalam roster tim (Linked List) untuk menemukan pemain yang mencetak goal/assist. Jika nama cocok, poin goal/assist pemain pada roster tersebut akan bertambah.
239 - 250: Melakukan pencarian di dalam array rankPemain. Jika data statistik individu pemain sudah ada di array, maka nilainya juga di-update.
252 - 258: Kondisi jika pemain belum tercatat di dalam array global rankPemain dan array belum penuh, maka memasukkan data pemain tersebut ke dalam array statistik pemain.
261 - 321: Fungsi menampilkan ranking statistik pemain individual.
267 – 273: Deklarasi objek array ranking goal dan assist serta inisialisasi pemain berdasarkan array rank pemain.
275 - 284: Bubble Sort untuk mengurutkan pemain berdasarkan statistik goal (dan assist jika goal sama) individual.
286 - 294: Bubble Sort untuk mengurutkan pemain berdasarkan statistik assist individual.
296 - 307: Menampilkan ranking pemain pencetak goal.
309 – 320: Menampilkan ranking pemain pemberi assist.
323 - 399: Fungsi pencatatan dan inisialisasi pertandingan
401: Fungsi menginisialisasi data Klub (input data klub dilakukan melalui fungsi ini)
402 - 406: Perulangan inisialisasi seluruh elemen dari Adjacency Matrix historiGraph menjadi false (belum ada pertandingan sama sekali di awal turnamen).
408 - 415: Inisialisasi fungsi untuk membuat object klub baru dengan menggunakan pendekatan modern Lambda Expression buatKlub untuk mempermudah instansiasi klub, dimana nama variabel/tipe data penampung fungsi ditentukan oleh compiler.
409 - 413: Inisialisasi klub baru ke dalam program.
417: Inisialisasi data tim dan pertandingan dummy untuk testing
  	
4.	Function Main: Hanya digunakan untuk menginisialiasi semua fungsi berbasarkan pilihan user pada menu.
