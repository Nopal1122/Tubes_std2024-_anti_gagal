#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

#define INF 999999      // Konstanta untuk jarak tak terhingga
#define MAX_NODES 42    // Jumlah maksimum node dalam graf (Gate, Gedung, TULT)

using namespace std;

// Struktur untuk graph
struct Graph {
    int matriksKetetanggaan[MAX_NODES][MAX_NODES]; // Matriks ketetanggaan untuk representasi graph
    string namaNode[MAX_NODES];                    // Array untuk nama node
    int jumlahNode;                                // Jumlah node yang ada dalam graph
};

void inisialisasiGraph(Graph &g);
void tambahNode(Graph &g, const string &namaNode);
void tambahKoneksi(Graph &g, const string &node1, const string &node2, int jarakMeter);
int cariIndeksNode(const Graph &g, const string &namaNode);
void tampilkanJalur(const int prev[], const Graph &g, const string &nodeAwal, const string &nodeTujuan);
void cariJalurTerpendek(const Graph &g, const string &nodeAwal, const string &nodeTujuan);

#endif // GRAPH_H
