#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>
#define firstVertex(G) G.firstVertex
#define namaTempat(V) V->namaTempat
#define nextVertex(V) V->nextVertex
#define firstEdge(V) V->firstEdge
#define nextEdge(E) E->nextEdge
#define lokasiAwal(E) E->lokasiAwal
#define lokasiTujuan(E) E->lokasiTujuan
#define namaJalan(E) E->namaJalan
#define jarak(E) E->jarak
#define waktuTempuh(E) E->waktuTempuh
using namespace std;

typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

struct vertex {
    string namaTempat;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct edge{
    string lokasiAwal;
    string lokasiTujuan;
    string namaJalan;
    int jarak;
    int waktuTempuh;
    adrEdge nextEdge;
};

struct graph {
    adrVertex firstVertex;
};

adrVertex createVertex(string namaLokasi);
adrEdge createEdge(string startPoint, string endPoint, string namaJalan, int jarak);
void initGraph(graph &G);
void addVertex(graph &G, string namaLokasi);
void addEdge(graph &G, string startPoint, string endPoint, string namaJalan, int jarak, int waktuTempuh);
void buildGraph(graph &G);
adrVertex findVertex(graph G, string namaLokasi);
adrEdge findEdge(adrVertex V, string namaJalan, string namaLokasi);
void allRouteToBuilding(graph G, string startPoint, string endPoint);
void findShortRoute(graph G, string startPoint, string endPoint);
void printGraph(graph G);
void deleteEdge(graph &G, string lokasi);
void deleteVertex(graph &G, string lokasi);
void findMostVisitedLocation(graph G);

void menu ();
void header();
void footer();
void nama_kelompok();

//Under Developing
void allRouteToBuilding(graph G, string startPoint, string endPoint);
void findRoutes(graph G, string awal, string akhir, string rute[], int &index, int totalJarak, int totalWaktu);
#endif // TUBES_H_INCLUDED
