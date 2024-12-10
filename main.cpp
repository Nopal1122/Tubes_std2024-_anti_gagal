#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Graph g;
    inisialisasiGraph(g);

    int jumlahNode;
    cout << "Masukkan jumlah node: ";
    cin >> jumlahNode;
    cin.ignore(); // Membersihkan input buffer setelah membaca angka

    // Input nama node
    for (int i = 0; i < jumlahNode; i++) {
        string nodeName;
        cout << "Masukkan nama titik lokasi " << i + 1 << ": ";
        getline(cin, nodeName);
        tambahNode(g, nodeName);
    }

    int jumlahKoneksi;
    cout << "Masukkan jumlah jalur (edges): ";
    cin >> jumlahKoneksi;
    cin.ignore();

    // Input koneksi antar node
    for (int i = 0; i < jumlahKoneksi; i++) {
        string node1, node2;
        int jarak;
        cout << "Masukkan nama titik lokasi pertama (misal: Gate A): ";
        getline(cin, node1);
        cout << "Masukkan nama titik lokasi ke 2 (misal: Gedung 1): ";
        getline(cin, node2);
        cout << "Masukkan jarak antar lokasi (dalam meter): ";
        cin >> jarak;
        cin.ignore();

        tambahKoneksi(g, node1, node2, jarak);
    }

    string nodeAwal, nodeTujuan;
    cout << "Masukkan titik awal: ";
    getline(cin, nodeAwal);
    cout << "Masukkan titiki tujuan: ";
    getline(cin, nodeTujuan);

    // Mencari jalur terpendek
    cariJalurTerpendek(g, nodeAwal, nodeTujuan);

    return 0;
}
