#include <iostream>
#include "tubes.h"
using namespace std;

int main()
{
    //Kamus Variabel
    int pilihan = 999, waktu = 0, jarak = 0, input = 999;
    string lokasiMulai, lokasiAkhir, jalan, deletedLokasi;
    adrVertex cariAwal, cariAkhir;

    //Mulai Program
    graph G;
    initGraph(G);
    buildGraph(G);
    header();
    nama_kelompok();
    header();

    while(pilihan != 0){
        header();
        menu();
        cin >> pilihan;
        switch(pilihan){
            case 1:
                header();
                cout << "Menu 1 " << endl;
                cout << "Seluruh Rute yang Tersedia" << endl;
                printGraph(G);
                break;
            case 2:
                header();
                cout << "Menu 2" << endl;
                cout << "Cari Semua Rute" << endl;
                cout << "Masukkan Nama Lokasi Awal : " ;
                cin >> lokasiMulai;
                cout << "Masukkan Nama Lokasi Tujuan : ";
                cin >> lokasiAkhir;
                allRouteToBuilding(G, lokasiMulai, lokasiAkhir);
                break;
            case 3:
                header();
                cout << "Menu 3" << endl;
                cout << "Mencari Rute Terpendek" << endl;
                cout << "Masukkan Nama Lokasi Awal : " ;
                cin >> lokasiMulai;
                cout << "Masukkan Nama Lokasi Tujuan : ";
                cin >> lokasiAkhir;

                cariAwal = findVertex(G, lokasiMulai);
                cariAkhir = findVertex(G, lokasiAkhir);

                if (cariAwal == NULL && cariAkhir == NULL){
                    cout << "Lokasi awal dan lokasi akhir yang anda masukkan tidak ditemukan" << endl;
                } else if (cariAwal == NULL && cariAkhir != NULL){
                    cout << "Lokasi awal yang anda masukkan tidak di temukan" << endl;
                } else if (cariAwal != NULL && cariAkhir == NULL){
                    cout << "Lokasi akhir yang anda masukkan tidak di temukan" << endl;
                } else {
                    findShortRoute(G, lokasiMulai, lokasiAkhir);
                }
                break;
            case 4:
                header();
                cout << "Menu 4" << endl;
                cout << "Menginformasikan gedung/lokasi Maintenance" << endl;

                cout << "Masukkan nama lokasi yang ingin dihapus: ";
                cin >> deletedLokasi;
                deleteVertex(G, deletedLokasi);
                break;
            
            case 5:
                cout << "Menu 5" << endl;
                cout << "Menambah Lokasi" << endl;
                cout << "1. Menambah Lokasi"<<endl;
                cout << "2. Menambah Rute"<<endl;
                cout << "Pilih : ";
                cin >> input;
                if(input == 1){
                    cout << "Masukkan nama lokasi yang ingin ditambahkan: ";
                    cin >> lokasiMulai;
                    addVertex(G, lokasiMulai);
                    cout << "Lokasi berhasil ditambahkan!!" << endl;
                } else if(input == 2){
                    cout << "Masukkan nama lokasi asal: ";
                    cin >> lokasiMulai;
                    cout << "Masukkan nama lokasi tujuan: ";
                    cin >> lokasiAkhir;
                    cout << "Masukkan nama jalan: ";
                    cin >> jalan;
                    cout << "Masukkan waktu tempuh: ";
                    cin >> waktu;
                    cout << "Masukkan jarak (dalam km): ";
                    cin >> jarak;
                    addEdge(G, lokasiMulai, lokasiAkhir, jalan, waktu, jarak);
                }
                break;
            case 6:
                header();
                cout << "Menu 6" << endl;
                findMostFrequentIntersection(G);
                break;
            case 0:
                header();
                cout << "Terima Kasih sudah Menggunakan Aplikasi Kami" << endl;
                header();
                break;
            default:
                cout << "Pilihan tidak Valid" << endl;
                break;
        }
    }
}
