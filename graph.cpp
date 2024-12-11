#include "graph.h"

// Fungsi untuk menginisialisasi graph baru
void inisialisasiGraph(Graph &g) {
    g.jumlahNode = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            g.matriksKetetanggaan[i][j] = (i == j) ? 0 : INF; // Set jarak antar node yang sama menjadi 0, lainnya INF
        }
    }
}

// Fungsi untuk menambahkan node ke dalam graph
void tambahNode(Graph &g, const string &namaNode) {
    if (g.jumlahNode < MAX_NODES) {
        // Cek apakah nama node sudah ada sebelumnya
        for (int i = 0; i < g.jumlahNode; i++) {
            if (g.namaNode[i] == namaNode) {
                cout << "Node \"" << namaNode << "\" sudah ada.\n";
                return;
            }
        }
        g.namaNode[g.jumlahNode++] = namaNode; // Tambahkan node baru
    } else {
        cout << "Maksimal jumlah node tercapai.\n";
    }
}

// Fungsi untuk menambahkan koneksi (edge) antar node
void tambahKoneksi(Graph &g, const string &node1, const string &node2, int jarakMeter) {
    if (jarakMeter <= 0) {
        cout << "Jarak harus lebih dari 0.\n";
        return;
    }
    int indeks1 = cariIndeksNode(g, node1);
    int indeks2 = cariIndeksNode(g, node2);

    if (indeks1 == -1 || indeks2 == -1) {
        cout << "Node \"" << (indeks1 == -1 ? node1 : node2) << "\" tidak ditemukan.\n";
        return;
    }

    // Cek apakah koneksi sudah ada
    if (g.matriksKetetanggaan[indeks1][indeks2] != INF) {
        cout << "Koneksi antara \"" << node1 << "\" dan \"" << node2 << "\" sudah ada.\n";
        return;
    }

    // Tambahkan koneksi jika belum ada
    g.matriksKetetanggaan[indeks1][indeks2] = jarakMeter;
    g.matriksKetetanggaan[indeks2][indeks1] = jarakMeter; // Koneksi dua arah
}


// Fungsi untuk mencari indeks node berdasarkan nama
int cariIndeksNode(const Graph &g, const string &namaNode) {
    for (int i = 0; i < g.jumlahNode; i++) {
        if (g.namaNode[i] == namaNode) return i;
    }
    return -1; // Node tidak ditemukan
}

// Fungsi untuk menampilkan jalur yang ditempuh
void tampilkanJalur(const int prev[], const Graph &g, const string &nodeAwal, const string &nodeTujuan) {
    int tujuanIndeks = cariIndeksNode(g, nodeTujuan);
    if (tujuanIndeks == -1) {
        cout << "Node tujuan \"" << nodeTujuan << "\" tidak ditemukan.\n";
        return;
    }

    cout << "Jalur yang harus ditempuh dari " << nodeAwal << " ke " << nodeTujuan << " adalah:\n";

    string jalur[MAX_NODES];
    int i = tujuanIndeks;
    int j = 0;

    // Susun jalur dari node tujuan ke node awal
    while (i != -1) {
        jalur[j++] = g.namaNode[i];
        i = prev[i];
    }

    // Cetak jalur dalam urutan yang benar
    for (int k = j - 1; k >= 0; k--) {
        cout << jalur[k];
        if (k != 0) cout << " -> ";
    }
    cout << endl;
}

// Fungsi untuk mencari jalur terpendek menggunakan algoritma Dijkstra
void cariJalurTerpendek(const Graph &g, const string &nodeAwal, const string &nodeTujuan) {
    int jarak[MAX_NODES];
    bool sudahDikunjungi[MAX_NODES] = {false};
    int prev[MAX_NODES]; // Array untuk melacak node sebelumnya

    for (int i = 0; i < g.jumlahNode; i++) {
        jarak[i] = INF;
        prev[i] = -1; // Inisialisasi node sebelumnya dengan -1 (belum ditemukan)
    }

    int indeksAwal = cariIndeksNode(g, nodeAwal);
    int indeksTujuan = cariIndeksNode(g, nodeTujuan);

    if (indeksAwal == -1 || indeksTujuan == -1) {
        cout << "Node \"" << (indeksAwal == -1 ? nodeAwal : nodeTujuan) << "\" tidak ditemukan.\n";
        return;
    }

    jarak[indeksAwal] = 0;

    for (int i = 0; i < g.jumlahNode - 1; i++) {
        int jarakMin = INF, nodeSaatIni = -1;

        // Cari node dengan jarak minimum yang belum dikunjungi
        for (int j = 0; j < g.jumlahNode; j++) {
            if (!sudahDikunjungi[j] && jarak[j] < jarakMin) {
                jarakMin = jarak[j];
                nodeSaatIni = j;
            }
        }

        if (nodeSaatIni == -1) break; // Tidak ada node yang dapat dijangkau
        sudahDikunjungi[nodeSaatIni] = true;

        // Perbarui jarak ke node tetangga
        for (int tetangga = 0; tetangga < g.jumlahNode; tetangga++) {
            if (!sudahDikunjungi[tetangga] && g.matriksKetetanggaan[nodeSaatIni][tetangga] != INF
                && jarak[nodeSaatIni] + g.matriksKetetanggaan[nodeSaatIni][tetangga] < jarak[tetangga]) {
                jarak[tetangga] = jarak[nodeSaatIni] + g.matriksKetetanggaan[nodeSaatIni][tetangga];
                prev[tetangga] = nodeSaatIni; // Simpan node sebelumnya
            }
        }
    }

    if (jarak[indeksTujuan] == INF) {
        cout << "Tidak ada jalur ke tujuan \"" << nodeTujuan << "\".\n";
    } else {
        double waktuEstimasiMenit = jarak[indeksTujuan] / (1.39 * 60);
        cout << "Jarak terpendek dari " << nodeAwal << " ke " << nodeTujuan
             << " adalah: " << jarak[indeksTujuan] << " meter.\n";
        cout << "Estimasi waktu tempuh: " << waktuEstimasiMenit << " menit.\n";

        // Tampilkan jalur yang ditempuh
        tampilkanJalur(prev, g, nodeAwal, nodeTujuan);
    }
}
