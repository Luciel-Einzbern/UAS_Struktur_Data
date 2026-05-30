#include <iostream>
#include <string>
using namespace std;

const int totalKlub = 10;
const int totalPemain = 100;

struct NodePemain {
    string namaPemain;
    string posisi;
    int nomorPunggung;
    int goal;
    int assist;
    NodePemain* next;
};

struct Klub {
    int id;
    string namaKlub;
    string asalNegara;
    int poin;
    NodePemain* rosterTim; 
};

struct StatistikPemain {
    string namaPemain;
    string namaKlub;
    int goal;
    int assist;
};

struct QueueJadwal {
    int idTim1;
    int idTim2;
    QueueJadwal* next;
};

struct StackRiwayat {
    string namaTim1;
    string namaTim2;
    int skorTim1;
    int skorTim2;
    StackRiwayat* next;
};

struct BSTTim {
    Klub* klubData;
    BSTTim* left;
    BSTTim* right;
};

struct GraphGroup {
    bool adjMatrix[totalKlub][totalKlub];
};

Klub* klasemen[totalKlub];
int jmlTim = 0;

StatistikPemain rankPemain[totalPemain];
int jmlRankPemain = 0;

QueueJadwal* frontQueue = NULL;
QueueJadwal* rearQueue = NULL;

StackRiwayat* topStack = NULL;

BSTTim* rootBST = NULL;

GraphGroup historiGraph;

void tambahPemain(NodePemain*& head, string nama, string posisi, int no) {
    NodePemain* newNode = new NodePemain;
    newNode->namaPemain = nama;
    newNode->posisi = posisi;
    newNode->nomorPunggung = no;
    newNode->goal = 0;
    newNode->assist = 0;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        NodePemain* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void insertBST(BSTTim*& root, Klub* data) {
    if (root == NULL) {
        root = new BSTTim;
        root->klubData = data;
        root->left = NULL;
        root->right = NULL;
    } else if (data->id < root->klubData->id) {
        insertBST(root->left, data);
    } else {
        insertBST(root->right, data);
    }
}

Klub* cariBST(BSTTim* root, int id) {
    if (root == NULL) {
        return NULL;
    }
    if (root->klubData->id == id) {
        return root->klubData;
    }
    if (id < root->klubData->id) {
        return cariBST(root->left, id);
    }
    return cariBST(root->right, id);
}

void enqueue(int id1, int id2) {
    QueueJadwal* newNode = new QueueJadwal;
    newNode->idTim1 = id1;
    newNode->idTim2 = id2;
    newNode->next = NULL;

    if (rearQueue == NULL) {
        frontQueue = rearQueue = newNode;
    } else {
        rearQueue->next = newNode;
        rearQueue = newNode;
    }
}

bool dequeue(int& id1, int& id2) {
    if (frontQueue == NULL) {
        return false;
    }

    QueueJadwal* temp = frontQueue;
    id1 = temp->idTim1;
    id2 = temp->idTim2;
    
    frontQueue = frontQueue->next;
    if (frontQueue == NULL) {
        rearQueue = NULL;
    }
    delete temp;
    return true;
}

void pushStack(string t1, string t2, int s1, int s2) {
    StackRiwayat* newNode = new StackRiwayat;
    newNode->namaTim1 = t1;
    newNode->namaTim2 = t2;
    newNode->skorTim1 = s1;
    newNode->skorTim2 = s2;
    newNode->next = topStack;
    topStack = newNode; 
}

void cetakStack() {
    if (topStack == NULL) {
        cout << "\nBelum ada riwayat pertandingan.\n";
        return;
    }

    StackRiwayat* temp = topStack;
    cout << "\n--- RIWAYAT PERTANDINGAN (TERBARU KE TERLAMA) ---\n";
    while (temp != NULL) {
        cout << temp->namaTim1 << " " << temp->skorTim1 << " - " << temp->skorTim2 << " " << temp->namaTim2 << "\n";
        temp = temp->next;
    }
}

void urutkanKlasemen() {
    for (int i = 0; i < jmlTim - 1; i++) {
        for (int j = 0; j < jmlTim - i - 1; j++) {
            if (klasemen[j]->poin < klasemen[j + 1]->poin) {
                Klub* temp = klasemen[j];
                klasemen[j] = klasemen[j + 1];
                klasemen[j + 1] = temp;
            }
        }
    }
}

void cariTimDiKlasemen(string nama) {
    urutkanKlasemen(); 
    bool found = false;
    
    for (int i = 0; i < jmlTim; i++) {
        if (klasemen[i]->namaKlub == nama) {
            cout << "\n--- KLUB DITEMUKAN ---\n";
            cout << "Peringkat  : " << i + 1 << "\n";
            cout << "Nama Klub  : " << klasemen[i]->namaKlub << "\n";
            cout << "Asal Negara: " << klasemen[i]->asalNegara << "\n";
            cout << "Poin       : " << klasemen[i]->poin << "\n";
            cout << "\nROSTER PEMAIN AKTIF:\n";
            
            NodePemain* p = klasemen[i]->rosterTim;
            while (p != NULL) {
                cout << "- " << p->namaPemain << " (" << p->posisi << ", No: " << p->nomorPunggung 
                     << ") | Goal: " << p->goal << " | Assist: " << p->assist << "\n";
                p = p->next;
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nKlub dengan nama '" << nama << "' tidak ditemukan.\n";
    }
}

void updateStatistik(string namaPem, string namaKlub, int tipe) {
    bool foundNode = false;

    for (int i = 0; i < jmlTim; i++) {
        if (klasemen[i]->namaKlub == namaKlub) {
            NodePemain* temp = klasemen[i]->rosterTim;

            while (temp != NULL) {
                if (temp->namaPemain == namaPem) {
                    if (tipe == 1) {
                        temp->goal++;
                    } else {
                        temp->assist++;
                    }
                    foundNode = true;
                    break;
                }
                temp = temp->next;
            }
            break;
        }
    }

    if (!foundNode) {
        cout << "    -> (Pemain tidak terdaftar resmi di klub, namun tetap dicatat di ranking umum)\n";
    }

    bool foundArray = false;
    for (int i = 0; i < jmlRankPemain; i++) {
        if (rankPemain[i].namaPemain == namaPem) {
            if (tipe == 1) {
                rankPemain[i].goal++;
            } else {
                rankPemain[i].assist++;
            }
            foundArray = true;
            break;
        }
    }
    
    if (!foundArray && jmlRankPemain < totalPemain) {
        rankPemain[jmlRankPemain].namaPemain = namaPem;
        rankPemain[jmlRankPemain].namaKlub = namaKlub;
        rankPemain[jmlRankPemain].goal = (tipe == 1 ? 1 : 0);
        rankPemain[jmlRankPemain].assist = (tipe == 2 ? 1 : 0);
        jmlRankPemain++;
    }
}

void tampilRankingPemain() {
    if (jmlRankPemain == 0) {
        cout << "\nBelum ada data pemain yang mencetak goal atau assist.\n";
        return;
    }

    StatistikPemain GoalRanking[totalPemain];
    StatistikPemain AssistRanking[totalPemain];

    for(int i = 0; i < jmlRankPemain; i++) {
        GoalRanking[i] = rankPemain[i];
        AssistRanking[i] = rankPemain[i];
    }

    for(int i = 0; i < jmlRankPemain - 1; i++) {
        for(int j = 0; j < jmlRankPemain - i - 1; j++) {
            if(GoalRanking[j].goal < GoalRanking[j+1].goal || 
              (GoalRanking[j].goal == GoalRanking[j+1].goal && GoalRanking[j].assist < GoalRanking[j+1].assist)) {
                StatistikPemain temp = GoalRanking[j];
                GoalRanking[j] = GoalRanking[j+1];
                GoalRanking[j+1] = temp;
            }
        }
    }

    for(int i = 0; i < jmlRankPemain - 1; i++) {
        for(int j = 0; j < jmlRankPemain - i - 1; j++) {
            if(AssistRanking[j].assist < AssistRanking[j+1].assist) {
                StatistikPemain temp = AssistRanking[j];
                AssistRanking[j] = AssistRanking[j+1];
                AssistRanking[j+1] = temp;
            }
        }
    }
    
    cout << "\n--- TOP GOAL ---\n";
    int noGoal = 0;
    for(int i = 0; i < jmlRankPemain; i++) {
        if (GoalRanking[i].goal > 0) {
            noGoal++;
            cout << noGoal << ". " << GoalRanking[i].namaPemain << " (" << GoalRanking[i].namaKlub 
             << ") | Goal: " << GoalRanking[i].goal << " | Assist: " << GoalRanking[i].assist << "\n";
        }
    }
    if (noGoal == 0) {
        cout << "Belum ada pemain yang mencetak goal.\n";
    }

    cout << "\n--- TOP ASSIST ---\n";
    int noAssist = 0;
    for(int i = 0; i < jmlRankPemain; i++) {
        if (AssistRanking[i].assist > 0) {
            noAssist++;
            cout << noAssist << ". " << AssistRanking[i].namaPemain << " (" << AssistRanking[i].namaKlub 
                 << ") | Assist: " << AssistRanking[i].assist << "\n";
        }
    }
    if (noAssist == 0) {
        cout << "Belum ada pemain yang memberikan assist.\n";
    }
}

void catatPertandingan() {
    int id1, id2;
    if (!dequeue(id1, id2)) {
        cout << "\nTidak ada jadwal pertandingan di antrean (Queue kosong).\n";
        return;
    }

    Klub* tim1 = cariBST(rootBST, id1);
    Klub* tim2 = cariBST(rootBST, id2);
    
    if(!tim1 || !tim2) return;

    cout << "\n=============================================\n";
    cout << " PERTANDINGAN: " << tim1->namaKlub << " VS " << tim2->namaKlub << "\n";
    cout << "=============================================\n";
    
    historiGraph.adjMatrix[id1][id2] = true;
    historiGraph.adjMatrix[id2][id1] = true;
    
    int goal1 = 0, goal2 = 0;

    cout << "Masukkan Skor " << tim1->namaKlub << ": ";
    while (!(cin >> goal1)) {
        cout << "Input tidak valid! Harap masukkan angka.\n";
        cout << "Masukkan Skor " << tim1->namaKlub << ": ";
        cin.clear(); 
        cin.ignore(); 
    }

    cout << "Masukkan Skor " << tim2->namaKlub << ": ";
    while (!(cin >> goal2)) {
        cout << "Input tidak valid! Harap masukkan angka.\n";
        cout << "Masukkan Skor " << tim2->namaKlub << ": ";
        cin.clear(); 
        cin.ignore(); 
    }

    cin.ignore();

    if (goal1 > goal2) { 
        tim1->poin += 3; 
    } else if (goal2 > goal1) { 
        tim2->poin += 3; 
    } else { 
        tim1->poin += 1; 
        tim2->poin += 1; 
    }

    for(int i = 0; i < goal1; i++) {
        string pencetak, assist;
        cout << "\n[Tim " << tim1->namaKlub << "] Gol ke-" << i+1 << " dicetak oleh: ";
        getline(cin, pencetak);
        updateStatistik(pencetak, tim1->namaKlub, 1);
        
        cout << "-> Assist oleh (Kosongi lalu tekan Enter jika tidak ada): ";
        getline(cin, assist);
        if(assist != "") {
            updateStatistik(assist, tim1->namaKlub, 2);
        }
    }
    
    for(int i = 0; i < goal2; i++) {
        string pencetak, assist;
        cout << "\n[Tim " << tim2->namaKlub << "] Gol ke-" << i+1 << " dicetak oleh: ";
        getline(cin, pencetak);
        updateStatistik(pencetak, tim2->namaKlub, 1);
        
        cout << "-> Assist oleh (Kosongi lalu tekan Enter jika tidak ada): ";
        getline(cin, assist);
        if(assist != "") {
            updateStatistik(assist, tim2->namaKlub, 2);
        }
    }

    pushStack(tim1->namaKlub, tim2->namaKlub, goal1, goal2);
    cout << "\nPertandingan selesai dicatat!\n";
}

void inisialisasiData() {
    for(int i = 0; i < totalKlub; i++) {
        for(int j = 0; j < totalKlub; j++) {
            historiGraph.adjMatrix[i][j] = false;
        }
    }

    auto buatKlub = [](int id, string nama, string negara) {
        Klub* k = new Klub;
        k->id = id; k->namaKlub = nama; k->asalNegara = negara;
        k->poin = 0; k->rosterTim = NULL;
        klasemen[jmlTim++] = k;
        insertBST(rootBST, k);
        return k;
    };

    Klub* k1 = buatKlub(0, "Chelsea FC", "Inggris");
    tambahPemain(k1->rosterTim, "Robert Sanchez", "Kiper", 1);
    tambahPemain(k1->rosterTim, "Levi Colwill", "Bek", 6);
    tambahPemain(k1->rosterTim, "Enzo Fernandez", "Gelandang", 8);
    tambahPemain(k1->rosterTim, "Cole Parmer", "Gelandang", 20);
    tambahPemain(k1->rosterTim, "Pedro Neto", "Penyerang", 7);
    tambahPemain(k1->rosterTim, "Christopher Nkunku", "Penyerang", 18);

    Klub* k2 = buatKlub(1, "Arsenal FC", "Inggris");
    tambahPemain(k2->rosterTim, "David Raya", "Kiper", 22);
    tambahPemain(k2->rosterTim, "William Saliba", "Bek", 2);
    tambahPemain(k2->rosterTim, "Martin Odegaard", "Gelandang", 8);
    tambahPemain(k2->rosterTim, "Declan Rice", "Gelandang", 41);
    tambahPemain(k2->rosterTim, "Bukayo Saka", "Penyerang", 7);
    tambahPemain(k2->rosterTim, "Gabriel Martinelli", "Penyerang", 11);

    Klub* k3 = buatKlub(2, "Manchester United", "Inggris");
    tambahPemain(k3->rosterTim, "Altay Bayindir", "Kiper", 1);
    tambahPemain(k3->rosterTim, "Lisandro Martinez", "Bek", 6);
    tambahPemain(k3->rosterTim, "Bruno Fernandes", "Gelandang", 8);
    tambahPemain(k3->rosterTim, "Casemiro", "Gelandang", 18);
    tambahPemain(k3->rosterTim, "Joshua Zirkzee", "Penyerang", 11);
    tambahPemain(k3->rosterTim, "Marcus Rashford", "Penyerang", 10);

    Klub* k4 = buatKlub(3, "Manchester City", "Inggris");
    tambahPemain(k4->rosterTim, "Stefan Ortega", "Kiper", 18);
    tambahPemain(k4->rosterTim, "Ruben Dias", "Bek", 3);
    tambahPemain(k4->rosterTim, "Rodri", "Gelandang", 16);
    tambahPemain(k4->rosterTim, "Kevin De Bruyne", "Gelandang", 17);
    tambahPemain(k4->rosterTim, "Erling Haaland", "Penyerang", 9);
    tambahPemain(k4->rosterTim, "Oscar Bob", "Penyerang", 52);

    Klub* k5 = buatKlub(4, "Liverpool", "Inggris");
    tambahPemain(k5->rosterTim, "Allison Becker", "Kiper", 1);
    tambahPemain(k5->rosterTim, "Virgil van Dijk", "Bek", 4);
    tambahPemain(k5->rosterTim, "Alexis Mac Allister", "Gelandang", 10);
    tambahPemain(k5->rosterTim, "Wataru Endo", "Gelandang", 3);
    tambahPemain(k5->rosterTim, "Cody Gakpo", "Penyerang", 18);
    tambahPemain(k5->rosterTim, "Luiz Dias", "Penyerang", 7);

    enqueue(0, 4); 
    enqueue(1, 2);
    enqueue(0, 3);
    enqueue(4, 2);
    enqueue(0, 2);
    enqueue(3, 1);
    enqueue(1, 4);
    enqueue(2, 3);
    enqueue(0, 1); 
    enqueue(3, 4); 
}

int main() {
    inisialisasiData();
    int pilihan;
    string searchNama;

    do {
        system("cls");
        cout << "\n=============================================\n";
        cout << " SISTEM MANAJEMEN TURNAMEN SEPAK BOLA C++\n";
        cout << "=============================================\n";
        cout << "1. Mainkan Jadwal Antrean\n";
        cout << "2. Lihat Klasemen Poin Klub\n";
        cout << "3. Lihat Ranking Goal/Assist Pemain\n";
        cout << "4. Cari Profil & Roster Klub\n";
        cout << "5. Lihat Riwayat Pertandingan\n";
        cout << "6. Cek Histori Head-to-Head\n";
        cout << "0. Keluar\n";
        cout << "=============================================\n";
        cout << "Pilih Menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                system("cls");
                catatPertandingan();
                system("pause");
                break;
            case 2:
                system("cls");
                urutkanKlasemen();
                cout << "\n--- KLASEMEN SEMENTARA ---\n";
                for(int i = 0; i < jmlTim; i++) {
                    cout << i+1 << ". " << klasemen[i]->namaKlub 
                         << " (Poin: " << klasemen[i]->poin << ")\n";
                }
                system("pause");
                break;
            case 3:
                system("cls");
                tampilRankingPemain();
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "\nMasukkan Nama Klub yang ingin dicari (Misal: " << klasemen[0]->namaKlub << "): ";
                getline(cin, searchNama);
                cariTimDiKlasemen(searchNama);
                system("pause");
                break;
            case 5:
                system("cls");
                cetakStack();
                system("pause");
                break;
            case 6:
                system("cls");
                cout << "\n--- HISTORI PERTEMUAN (GRAPH 2D) ---\n";
                for(int i = 0; i < jmlTim; i++) {
                    for(int j = i + 1; j < jmlTim; j++) {
                        if(historiGraph.adjMatrix[klasemen[i]->id][klasemen[j]->id]) {
                            cout << "[V] Pernah Bertanding : " << klasemen[i]->namaKlub << " vs " << klasemen[j]->namaKlub << "\n";
                        } else {
                            cout << "[X] Belum Bertanding  : " << klasemen[i]->namaKlub << " vs " << klasemen[j]->namaKlub << "\n";
                        }
                    }
                }
                system("pause");
                break;
            case 0:
                cout << "Menutup program. Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
