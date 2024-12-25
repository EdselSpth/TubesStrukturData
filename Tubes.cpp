#include <iostream>
#include "tubes.h"
using namespace std;

adrVertex createVertex(string namaLokasi){
    // membuat vertex (tempat)
    adrVertex V = new vertex;
    namaTempat(V) = namaLokasi;
    nextVertex(V) = NULL;
    firstEdge(V) = NULL;
    return V;
}

adrEdge createEdge(string startPoint, string endPoint, string namaJalan, int jarak, int waktuTempuh){
    //membuat edge (jalan)
    adrEdge E = new edge;
    lokasiAwal(E) = startPoint;
    lokasiTujuan(E) = endPoint;
    namaJalan(E) = namaJalan;
    jarak(E) = jarak;
    waktuTempuh(E) = waktuTempuh;
    nextEdge(E) = NULL;
    return E;
}

void initGraph(graph &G){
    // insiasi graph
    firstVertex(G) = NULL;
}

void addVertex(graph &G, string namaLokasi){
    // menambahkan vertex (tempat) ke graph
    adrVertex V;
    V = createVertex(namaLokasi);
    if(firstVertex(G) == NULL){
        firstVertex(G) = V;
    } else {
        adrVertex P = firstVertex(G);
        while(nextVertex(P)!= NULL){
            P = nextVertex(P);
        }
        nextVertex(P) = V;
    }
}

adrVertex findVertex(graph G, string namaLokasi){
    // mencari vertex (gedung) yang memiliki nama yang sama dengan input
    adrVertex P = firstVertex(G);
    while(P!= NULL){
        if (namaTempat(P) == namaLokasi){
            return P;
        }
        P = nextVertex(P);
    }
    return NULL;
}

void addEdge(graph &G, string startPoint, string endPoint, string namaJalan, int jarak, int waktuTempuh){
    // Mencari vertex yang sesuai
    adrVertex V1 = findVertex(G, startPoint);
    adrVertex V2 = findVertex(G, endPoint);

    // Pastikan vertex ditemukan
    if (V1 != NULL && V2 != NULL) {
        // Membuat edge untuk kedua arah
        adrEdge E = createEdge(startPoint, endPoint, namaJalan, jarak, waktuTempuh);
        adrEdge E_reverse = createEdge(endPoint, startPoint, namaJalan, jarak, waktuTempuh);
        // Menambahkan edge untuk gedung awal
        if (firstEdge(V1) == NULL) {
            firstEdge(V1) = E;
        } else {
            adrEdge P = firstEdge(V1);
            while (nextEdge(P) != NULL) {
                P = nextEdge(P);
            }
            nextEdge(P) = E;
        }

        // Menambahkan edge untuk gedung tujuan (biar grafnya dua arah)
        if (firstEdge(V2) == NULL) {
            firstEdge(V2) = E_reverse;
        } else {
            adrEdge P = firstEdge(V2);
            while (nextEdge(P) != NULL) {
                P = nextEdge(P);
            }
            nextEdge(P) = E_reverse;
        }
    }
}

void buildGraph(graph &G){
    addVertex(G, "Gedung_Sate");
    addVertex(G, "Cimahi");
    addVertex(G, "Margaasih");
    addVertex(G, "UNPAD");
    addVertex(G, "Telkom");
    addVertex(G, "Pengalengan");
    addVertex(G, "Al_Jabbar");
    addVertex(G, "Ciwidey");
    addVertex(G, "UPI");

    addEdge(G,"Gedung_Sate","Cimahi","Jl_Babakan Ciparay",8,20);
    addEdge(G,"Gedung_Sate","Margaasih","Jl. Kopo",7,30);
    addEdge(G,"Gedung_Sate","Al_Jabbar","Jl. Sumatera",13,40);
    addEdge(G,"Gedung_Sate","UNPAD","Jl. Riau",25,80);
    addEdge(G,"Telkom","Pengalengan","Jl. Raya Banjaran",6,100);
    addEdge(G,"Telkom","Margaasih","Jl. Soekarno Hatta",6,20);
    addEdge(G,"Telkom","Gedung_Sate","Jl. Batununggal",9,35);
    addEdge(G,"Telkom","Al_Jabbar","Jl. Soekarno Hatta",13,42);
    addEdge(G,"Margaasih","Ciwidey","Jl. Ciputh",28,85);
    addEdge(G,"Margaasih","Cimahi","Jl. Soekarno Hatta",12,30);
    addEdge(G,"UPI","Gedung_Sate","Jl. Maluku",8,20);
    addEdge(G,"Al_Jabbar","UNPAD","Jl. Soekarno Hatta",7,18);

}

void findShortRoute(graph G, string startPoint, string endPoint) {

    adrVertex start = findVertex(G, startPoint);
    adrVertex target = findVertex(G, endPoint);

    if (start == NULL || target == NULL) {
        cout << "Lokasi tidak ditemukan!" << endl;
        return;
    }


    string vertices[100];
    int distances[100];
    int times[100];
    string previous[100];
    bool visited[100];
    bool allVisited = false;
    int vertexCount = 0;

    //set nilai jarak dan waktu ke 9999
    adrVertex V = firstVertex(G);
    while (V != NULL) {
        vertices[vertexCount] = namaTempat(V);
        distances[vertexCount] = 9999;
        times[vertexCount] = 9999;
        previous[vertexCount] = "";
        visited[vertexCount] = false;
        V = nextVertex(V);
        vertexCount++;
    }


    int startIndex = -1;
    int i = 0;
    while (i < vertexCount && startIndex == -1) {
        if (vertices[i] == startPoint) {
            startIndex = i;
            distances[i] = 0;
            times[i] = 0;
        }
        i++;
    }


    if (startIndex == -1) {
        cout << "Lokasi awal tidak ditemukan!" << endl;
        return;
    }

    // Proses utama algoritma
    for (int i = 0; i < vertexCount; i++) {

        int minDistance = 9999;
        int currentIndex = -1;
        for (int j = 0; j < vertexCount; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                currentIndex = j;
            }
        }


        if (currentIndex == -1) {
            allVisited = true;
        }
        visited[currentIndex] = true;

        // Perbarui jarak dan waktu untuk tetangga-tetangga
        adrVertex currentVertex = findVertex(G, vertices[currentIndex]);
        adrEdge edge = firstEdge(currentVertex);

        while (edge != NULL) {
            // Cari indeks tetangga
            int neighborIndex = -1;
            int j = 0;
            while (j < vertexCount && neighborIndex == -1) {
                if (vertices[j] == lokasiTujuan(edge)) {
                    neighborIndex = j;
                }
                j++;
            }

            // Perbarui jarak dan waktu jika menemukan rute lebih pendek
            if (neighborIndex != -1 && distances[currentIndex] + jarak(edge) < distances[neighborIndex]) {
                distances[neighborIndex] = distances[currentIndex] + jarak(edge);
                times[neighborIndex] = times[currentIndex] + waktuTempuh(edge);
                previous[neighborIndex] = vertices[currentIndex];
            }

            edge = nextEdge(edge);
        }
    }

    // Membangun rute terpendek
    int endIndex = -1;
    int k = 0;
    while (k < vertexCount && endIndex == -1) {
        if (vertices[k] == endPoint) {
            endIndex = k;
        }
        k++;
    }

    if (endIndex == -1 || distances[endIndex] == 9999) {
        cout << "Tidak ada rute dari " << startPoint << " ke " << endPoint << endl;
        return;
    }

    string path[100];
    int pathIndex = 0;
    int currentIndex = endIndex;

    while (currentIndex != -1 && vertices[currentIndex] != "") {
        path[pathIndex] = vertices[currentIndex];
        pathIndex++;

        string prev = previous[currentIndex];
        currentIndex = -1;
        int i = 0;
        while (i < vertexCount && currentIndex == -1) {
            if (vertices[i] == prev) {
                currentIndex = i;
            }
            i++;
        }
    }
    // Tampilkan rute terpendek
    cout << "Rute terpendek dari " << startPoint << " ke " << endPoint << ": " << endl;
    for (int i = pathIndex - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;


    cout << "Total jarak: " << distances[endIndex] << " km" << endl;
    cout << "Total waktu: " << times[endIndex] << " menit" << endl;
}

void deleteEdge(graph &G, string lokasi) {
    adrVertex V = findVertex(G, lokasi);
    if (V == NULL) {
        cout << "Lokasi " << lokasi << " tidak ditemukan!" << endl;
        return;
    }

    firstEdge(V) = NULL;

    adrVertex P = firstVertex(G);
    while (P != NULL) {
        adrEdge prev = NULL;
        adrEdge tempEdge = firstEdge(P);
        while (tempEdge != NULL) {
            if (lokasiTujuan(tempEdge) == lokasi) {
                if (prev == NULL) {
                    firstEdge(P) = nextEdge(tempEdge);
                } else {
                    nextEdge(prev) = nextEdge(tempEdge);
                }
                adrEdge temp = tempEdge;
                tempEdge = nextEdge(tempEdge);
                nextEdge(temp) = NULL;
            } else {
                prev = tempEdge;
                tempEdge = nextEdge(tempEdge);
            }
        }
        P = nextVertex(P);
    }
}

void deleteVertex(graph &G, string lokasi) {
    adrVertex V = findVertex(G, lokasi);
    if (V == NULL) {
        cout << "Lokasi " << lokasi << " tidak ditemukan!" << endl;
        return;
    }
    // Hapus semua edge yang terkait dengan vertex (baik keluar maupun masuk)
    deleteEdge(G, lokasi);

    // Hapus vertex dari daftar vertex
    if (firstVertex(G) == V) {
        firstVertex(G) = nextVertex(V);
        nextVertex(V) = NULL;
    } else {
        adrVertex prev = NULL;
        adrVertex temp = firstVertex(G);
        while (temp != NULL && temp != V) {
            prev = temp;
            temp = nextVertex(temp);
        }
        if (prev != NULL) {
            nextVertex(prev) = nextVertex(V);
            nextVertex(V) = NULL;
        }
    }
    cout << "Lokasi " << lokasi << " berhasil dihapus!" << endl;
}

void printGraph(graph G) {
    adrVertex V = firstVertex(G);
    if (V == NULL) {
        cout << "Tidak ada Lokasi!!" << endl;
        return;
    }

    while (V != NULL) {
        cout << "Nama Tempat: " << namaTempat(V) << endl;

        adrEdge E = firstEdge(V);
        if (E == NULL) {
            cout << "\tTidak ada jalan yang menghubungkan ke tempat lain." << endl;
        } else {
            while (E != NULL) {
                cout << "\t -> " << lokasiTujuan(E)
                     << ", Jalan: " << namaJalan(E)
                     << ", Waktu: " << waktuTempuh(E)
                     << " menit, Jarak: " << jarak(E) << " Km" << endl;
                E = nextEdge(E);
            }
        }

        cout << endl;
        V = nextVertex(V);
    }
}


void menu(){
    // menu program
    cout << "Menu Utama" << endl;
    cout << "(1) Print Seluruh Graph" << endl;
    cout << "(2) Cari Semua Rute Menuju Lokasi" << endl;
    cout << "(3) Cari Rute Terpendek Menuju Lokasi" << endl;
    cout << "(4) Menginfokan Lokasi Maintanance" << endl;
  
    cout << "(5) Tambah Lokasi atau jalan" << endl;
    cout << "(6) Lokasi atau persimpangan teramai" << endl;
    cout << "(0) Keluar" << endl;
    cout << "Pilih menu: ";
}


void header(){
    // header program
    cout << "=======================================================================" << endl;
}


void nama_kelompok(){
    cout << "                  Aplikasi Navigasi Kota Bandung" << endl;
    cout  << "               Edsel Septa Haryanto | 103022300016" << endl;
    cout << "                   Muhammad Fauzan | 103022300065" << endl;
}

//Under Developing
void allRouteToBuilding(graph G, string startPoint, string endPoint) {
    // Function Mencari Semua Rute dari lokasi A ke Lokasi B
    string rute[100];
    int index = 0;

    adrVertex cariAwalan = findVertex(G, startPoint);
    adrVertex cariAkhir = findVertex(G, endPoint);
    int totalJarak = 0;
    int totalWaktu = 0;

    if (cariAwalan == NULL && cariAkhir == NULL){
        cout << "Lokasi awal dan lokasi akhir yang anda masukkan tidak ditemukan" << endl;
    } else if (cariAwalan == NULL && cariAkhir != NULL){
        cout << "Lokasi awal yang anda masukkan tidak di temukan" << endl;
    } else if (cariAwalan != NULL && cariAkhir == NULL){
        cout << "Lokasi akhir yang anda masukkan tidak di temukan" << endl;
    } else {
        findRoutes(G, startPoint, endPoint, rute, index, totalJarak, totalWaktu);
    }
}

void findRoutes(graph G, string awal, string akhir, string rute[], int &index, int totalJarak, int totalWaktu) {
    // Mencari Rute dengan algoritma dfs (mencari dulu sebuah jalur mendalam baru kembali)
    rute[index++] = awal;
    if (awal == akhir) {
        for (int i = 0; i < index; i++) {
            cout << rute[i];
            if (i < index - 1) {
                cout << " -> ";
            }
        }
        cout << " | Total Jarak: " << totalJarak << " km, Total Waktu: " << totalWaktu << " menit" << endl;
    } else {
        adrVertex posisiSekarang = findVertex(G, awal);
        if (posisiSekarang != NULL) {
            adrEdge edge = firstEdge(posisiSekarang);
            while (edge != NULL){
                bool alreadyInPath = false;
                for (int i = 0; i < index; i++) {
                    if (rute[i] == lokasiTujuan(edge)) {
                        alreadyInPath = true;
                    }
                }
                if (!alreadyInPath) {
                    findRoutes(G, lokasiTujuan(edge), akhir, rute, index, totalJarak + jarak(edge), totalWaktu + waktuTempuh(edge));
                }
                edge = nextEdge(edge);
            }
        }
    }
    index--;
}


void findMostVisitedLocation(graph G) {
    if (firstVertex(G) == NULL) {
        cout << "Graf kosong! Tidak ada lokasi yang terdaftar." << endl;
        return;
    }

    string namaTempat[100];
    int frekuensi[100] = {0};
    int jumlahTempat = 0;

    adrVertex V = firstVertex(G);
    while (V != NULL) {
        namaTempat[jumlahTempat] = namaTempat(V);
        jumlahTempat++;
        V = nextVertex(V);
    }

    V = firstVertex(G);
    while (V != NULL) {
        adrEdge E = firstEdge(V);
        while (E != NULL) {
            for (int i = 0; i < jumlahTempat; i++) {
                if (namaTempat[i] == namaTempat(V)) {
                    frekuensi[i]++;
                }
            }
            for (int i = 0; i < jumlahTempat; i++) {
                if (namaTempat[i] == lokasiTujuan(E)) {
                    frekuensi[i]++;
                }
            }
            E = nextEdge(E);
        }
        V = nextVertex(V);
    }


    int maxFrekuensi = 0;
    string tempatTerbanyak = "";
    for (int i = 0; i < jumlahTempat; i++) {
        if (frekuensi[i] > maxFrekuensi) {
            maxFrekuensi = frekuensi[i];
            tempatTerbanyak = namaTempat[i];
        }
    }
    cout << "Tempat yang dapat dijangkau langsung dari banyak lokasi adalah : " << tempatTerbanyak << endl;
    cout << "Jumlah tempat : " << maxFrekuensi/2 << " kali." << endl;
    cout << "Lokasi-lokasi yang dapat mengakses ke " << tempatTerbanyak << " adalah: " << endl;
    V = firstVertex(G);
    while (V != NULL) {
        adrEdge E = firstEdge(V);
        while (E != NULL) {
            if (lokasiTujuan(E) == tempatTerbanyak) {
                cout << namaTempat(V) << "  ";
            }
            E = nextEdge(E);
        }
        V = nextVertex(V);
    }
    cout << endl;
}
