#include "graph.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    Graph g;
    inisialisasiGraph(g);

    // Daftar semua node
    const string gedung[] = {
        "Gate 1", "Gate 2", "Gate 3", "Gate 4",
        "Telyu Oplib", "Gedung Ekonomi Bisnis",
        "Jln Telekomunikasi", "Parkiran TULT", "TULT",
        "Fakultas Ilmu Terapan", "Alumni Coffee Univ Telkom",
        "Telkom University Convention Hall", "Parkiran GKU",
        "Asrama Laki", "Gedung Bangkit", "Menara Eiffel Telkom University",
        "GKU", "Masjid MSU"
    };
    const int jumlahNode = sizeof(gedung) / sizeof(gedung[0]);

    for (int i = 0; i < jumlahNode; i++) {
        tambahNode(g, gedung[i]);
    }

    // Data koneksi antar node dari masing-masing gerbang
    struct Koneksi {
        string node1;
        string node2;
        int jarak;
    };

    const Koneksi koneksiGate1[] = {
        {"Gate 1", "Telyu Oplib", 50},
        {"Telyu Oplib", "Gedung Ekonomi Bisnis", 50},
        {"Gedung Ekonomi Bisnis", "Jln Telekomunikasi", 250},
        {"Jln Telekomunikasi", "Parkiran TULT", 380},
        {"Parkiran TULT", "TULT", 70},
    };
    const int jumlahKoneksiGate1 = sizeof(koneksiGate1) / sizeof(koneksiGate1[0]);

    const Koneksi koneksiGate2[] = {
        {"Gate 2", "Fakultas Ilmu Terapan", 50},
        {"Fakultas Ilmu Terapan", "Alumni Coffee Univ Telkom", 100},
        {"Alumni Coffee Univ Telkom", "Telkom University Convention Hall", 275},
        {"Telkom University Convention Hall", "Parkiran GKU", 150},
        {"Parkiran GKU", "Asrama Laki", 180},
        {"Asrama Laki", "TULT", 200},
    };
    const int jumlahKoneksiGate2 = sizeof(koneksiGate2) / sizeof(koneksiGate2[0]);

    const Koneksi koneksiGate3[] = {
        {"Gate 3", "Gedung Bangkit", 50},
        {"Gedung Bangkit", "Menara Eiffel Telkom University", 50},
        {"Menara Eiffel Telkom University", "GKU", 250},
        {"GKU", "Asrama Laki", 380},
        {"Asrama Laki", "TULT", 380},
    };
    const int jumlahKoneksiGate3 = sizeof(koneksiGate3) / sizeof(koneksiGate3[0]);

    const Koneksi koneksiGate4[] = {
        {"Gate 4", "Masjid MSU", 50},
        {"Masjid MSU", "GKU", 400},
        {"GKU", "Asrama Laki", 250},
        {"Asrama Laki", "TULT", 200},
    };
    const int jumlahKoneksiGate4 = sizeof(koneksiGate4) / sizeof(koneksiGate4[0]);

    // Tambahkan semua koneksi ke dalam graph
    auto tambahkanSemuaKoneksi = [&](const Koneksi koneksi[], int jumlah) {
        for (int i = 0; i < jumlah; i++) {
            tambahKoneksi(g, koneksi[i].node1, koneksi[i].node2, koneksi[i].jarak);
        }
    };

    tambahkanSemuaKoneksi(koneksiGate1, jumlahKoneksiGate1);
    tambahkanSemuaKoneksi(koneksiGate2, jumlahKoneksiGate2);
    tambahkanSemuaKoneksi(koneksiGate3, jumlahKoneksiGate3);
    tambahkanSemuaKoneksi(koneksiGate4, jumlahKoneksiGate4);

    // Menu interaktif
    int pilihan;
    do {
        cout << "\n==== MENU ====\n";
        cout << "1. Tampilkan Semua Titik lokasi\n";
        cout << "2. Tambahkan lokasi Baru\n";
        cout << "3. Tambahkan Koneksi Baru\n";
        cout << "4. Cari Jalur Terpendek\n";
        cout << "6. Temukan Gedung/Node yang Paling Sering Dilewati\n";
        cout << "7. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan newline dari buffer input

        switch (pilihan) {
        case 1: {
            cout << "\nDaftar Node:\n";
            for (int i = 0; i < g.jumlahNode; i++) {
                cout << "- " << g.namaNode[i] << endl;
            }
            break;
        }
        case 2: {
            string namaNode;
            cout << "\nMasukkan nama lokasi baru: ";
            getline(cin, namaNode);
            tambahNode(g, namaNode);
            break;
        }
        case 3: {
            string node1, node2;
            int jarak;
            cout << "\nMasukkan nama node pertama: ";
            getline(cin, node1);
            cout << "Masukkan nama node kedua: ";
            getline(cin, node2);
            cout << "Masukkan jarak antara kedua node (meter): ";
            cin >> jarak;
            tambahKoneksi(g, node1, node2, jarak);
            break;
        }
        case 4: {
            string nodeAwal, nodeTujuan;
            cout << "\nMasukkan titik awal: ";
            getline(cin, nodeAwal);
            cout << "Masukkan titik tujuan: ";
            getline(cin, nodeTujuan);
            cariJalurTerpendek(g, nodeAwal, nodeTujuan);
            break;
        }
        case 5:{
            cout << "\nKeluar dari program. Terima kasih!\n";
            break;
        default:
            cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
        }
         case 6: {
            gedungPalingRamai(g);
            break;
        }
        }
    } while (pilihan != 7);

    return 0;
}
