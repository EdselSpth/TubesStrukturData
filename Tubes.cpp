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
        cout << "Gedung tidak ditemukan!" << endl;
        return;
    }

    int distances[100];  // Jarak ke setiap vertex
    string previous[100];  // Vertex sebelumnya untuk rute
    bool visited[100] = {false};  // Menandai apakah vertex sudah dikunjungi

    // Inisialisasi jarak
    adrVertex temp = firstVertex(G);
    int index = 0;
    while (temp != NULL) {
        distances[index] = 9999;  // Set jarak awal sangat besar
        previous[index] = "";
        temp = nextVertex(temp);
        index++;
    }

    // Mencari indeks gedung awal
    int startIndex = -1;
    temp = firstVertex(G);
    index = 0;
    while (temp != NULL) {
        if (namaTempat(temp) == startPoint) {
            startIndex = index;
        }
        temp = nextVertex(temp);
        index++;
    }

    if (startIndex == -1) {
        cout << "Lokasi Awal tidak ditemukan!" << endl;
        return;
    }

    distances[startIndex] = 0;

    // Langkah utama: Repeat until semua vertex dikunjungi
    bool allVisited = false;
    while (!allVisited) {
        // Mencari vertex dengan jarak terkecil yang belum dikunjungi
        int minDistance = 9999;
        int minIndex = -1;

        // Cari vertex dengan jarak terkecil
        temp = firstVertex(G);
        index = 0;
        while (temp != NULL) {
            if (!visited[index] && distances[index] < minDistance) {
                minDistance = distances[index];
                minIndex = index;
            }
            temp = nextVertex(temp);
            index++;
        }

        // Jika tidak ada vertex yang tersisa untuk dikunjungi
        if (minIndex == -1) {
            allVisited = true; // Semua vertex telah dikunjungi
        } else {
            // Tandai vertex sebagai sudah dikunjungi
            visited[minIndex] = true;

            // Ambil vertex saat ini dari indeks
            temp = firstVertex(G);
            index = 0;
            while (index != minIndex) {
                temp = nextVertex(temp);
                index++;
            }

            adrVertex currentVertex = temp;

            // Perbarui jarak ke tetangga-tetangga
            adrEdge edge = firstEdge(currentVertex);
            while (edge != NULL) {
                int neighborIndex = -1;
                temp = firstVertex(G);
                index = 0;
                while (temp != NULL) {
                    if (namaTempat(temp) == lokasiTujuan(edge)) {
                        neighborIndex = index;
                    }
                    temp = nextVertex(temp);
                    index++;
                }

                // Jika ditemukan tetangga yang belum dikunjungi
                if (neighborIndex != -1) {
                    int newDistance = distances[minIndex] + edge->jarak;
                    if (newDistance < distances[neighborIndex]) {
                        distances[neighborIndex] = newDistance;
                        previous[neighborIndex] = currentVertex->namaTempat;
                    }
                }
                edge = nextEdge(edge);
            }
        }
    }

    // Membangun rute terpendek
    string path[100];
    int pathIndex = 0;
    string current = endPoint;
    int totalDistance = 0;  // Total jarak
    int totalTime = 0;  // Total waktu
    while (current != "") {
        path[pathIndex] = current;
        pathIndex++;
        int idx = -1;
        temp = firstVertex(G);
        index = 0;
        while (temp != NULL) {
            if (namaTempat(temp) == current) {
                idx = index;
            }
            temp = nextVertex(temp);
            index++;
        }
        if (idx != -1) {
            current = previous[idx];
            // Menambahkan jarak dan waktu dari edge ke total
            adrVertex currentVertex = firstVertex(G);
            index = 0;
            while (index != idx) {
                currentVertex = nextVertex(currentVertex);
                index++;
            }
            adrEdge edge = firstEdge(currentVertex);
            while (edge != NULL) {
                if (lokasiTujuan(edge) == current) { // Pastikan kita menemukan edge yang tepat
                    totalDistance += jarak(edge);
                    totalTime += waktuTempuh(edge);
                    break; // Keluar dari loop setelah menemukan edge yang sesuai
                }
                edge = nextEdge(edge);
            }
        } else {
            current = ""; // Jika tidak ada previous, berarti kita sudah selesai.
        }
    }

    // Menampilkan rute terpendek
    cout << "Rute terpendek dari " << startPoint << " ke " << endPoint << ": " << endl;
    for (int i = pathIndex - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) {
            cout << " -> ";
        }
    }
    cout << endl;

    // Menampilkan total jarak dan waktu
    cout << "Total jarak: " << totalDistance << " km" << endl;
    cout << "Total waktu: " << totalTime << " menit" << endl;

}

void findMostFrequentIntersection(graph G) {
    if (firstVertex(G) == NULL) {
        cout << "Graf kosong! Tidak ada persimpangan untuk dianalisis." << endl;
        return;
    }

    // Inisialisasi array untuk menyimpan nama tempat dan frekuensi
    string namaTempat[100]; 
    int frekuensi[100] = {0}; 
    int jumlahTempat = 0;

    // Iterasi melalui semua vertex untuk mencatat nama tempat
    adrVertex V = firstVertex(G);
    while (V != NULL) {
        // Tambahkan nama tempat ke array
        namaTempat[jumlahTempat] = namaTempat(V);
        jumlahTempat++;

        V = nextVertex(V);
    }

    // Iterasi melalui semua edge untuk menghitung frekuensi
    V = firstVertex(G);
    while (V != NULL) {
        adrEdge E = firstEdge(V);
        while (E != NULL) {
            // Tambahkan frekuensi untuk lokasi awal
            for (int i = 0; i < jumlahTempat; i++) {
                if (namaTempat[i] == namaTempat(V)) {
                    frekuensi[i]++;
                }
            }

            // Tambahkan frekuensi untuk lokasi tujuan
            for (int i = 0; i < jumlahTempat; i++) {
                if (namaTempat[i] == lokasiTujuan(E)) {
                    frekuensi[i]++;
                }
            }

            E = nextEdge(E);
        }
        V = nextVertex(V);
    }

    // Cari tempat dengan frekuensi tertinggi
    int maxFrekuensi = 0;
    string tempatTerbanyak = "";
    for (int i = 0; i < jumlahTempat; i++) {
        if (frekuensi[i] > maxFrekuensi) {
            maxFrekuensi = frekuensi[i];
            tempatTerbanyak = namaTempat[i];
        }
    }

    // Cetak hasil
    cout << "Tempat atau persimpangan yang paling sering dilewati adalah: " << tempatTerbanyak << endl;
    cout << "Frekuensi: " << maxFrekuensi << " kali." << endl;
}

void deleteEdge(graph &G, string lokasi) {
    adrVertex V = findVertex(G, lokasi);
    if (V == NULL) {
        cout << "Lokasi " << lokasi << " tidak ditemukan!" << endl;
        return;
    }

    // Hapus semua edge yang keluar dari V
    adrEdge E = firstEdge(V);
    while (E != NULL) {
        adrEdge temp = E;
        E = nextEdge(E);
        delete temp;
    }
    firstEdge(V) = NULL;

    // Hapus semua edge yang mengarah ke V
    for (adrVertex P = firstVertex(G); P != NULL; P = nextVertex(P)) {
        if (P != V) {
            // Cari edge yang mengarah ke gedung yang akan dihapus
            adrEdge prev = NULL;
            adrEdge curr = firstEdge(P);
            while (curr != NULL) {
                if (lokasiTujuan(curr) == lokasi) {
                    if (prev == NULL) {
                        firstEdge(P) = nextEdge(curr);
                    } else {
                        nextEdge(prev) = nextEdge(curr);
                    }
                    delete curr;
                    break;
                }
                prev = curr;
                curr = nextEdge(curr);
            }
        }
    }
}

void deleteVertex(graph &G, string gedung) {
    adrVertex V = findVertex(G, gedung);
    if (V == NULL) {
        cout << "Vertex " << gedung << " tidak ditemukan!" << endl;
        return;
    }

    // Hapus semua edge yang mengarah ke dan dari vertex tersebut
    deleteEdge(G, gedung);

    // Hapus vertex dari daftar vertex
    if (firstVertex(G) == V) {
        firstVertex(G) = nextVertex(V);
    } else {
        adrVertex prev = NULL;
        adrVertex curr = firstVertex(G);
        while (curr != NULL) {
            if (curr == V) {
                nextVertex(prev) = nextVertex(curr);
                break;
            }
            prev = curr;
            curr = nextVertex(curr);
        }
    }

    // Hapus node vertex itu sendiri
    delete V;
    cout << "Vertex " << gedung << " berhasil dihapus!" << endl;
}

void printGraph(graph G) {
    adrVertex V = firstVertex(G);
    if (V == NULL) {
        cout << "Tidak ada Gedung!!" << endl;
        return;
    }

    while (V != NULL) {
        cout << "Nama Tempat: " << namaTempat(V) << endl;

        adrEdge E = firstEdge(V);
        if (E == NULL) {
            cout << "\tTidak ada jalan yang menghubungkan ke tempat lain." << endl;
        } else {
            while (E != NULL) {
                cout << "\tTujuan: " << lokasiTujuan(E)
                     << " ,Jalan: " << namaJalan(E)
                     << " ,Waktu: " << waktuTempuh(E)
                     << " menit ,Jarak: " << jarak(E) << " Km" << endl;
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
    cout << "(2) Cari Semua Rute Menuju Gedung" << endl;
    cout << "(3) Cari Rute Terpendek Menuju Gedung" << endl;
    cout << "(4) Menginfokan Gedung Maintanance" << endl;
    cout << "(5) Mencari Gedung Maintenance atau Nonaktif" << endl;
    cout << "(6) Tambah Gedung" << endl;
    cout << "(7) Tempat atau Persimpangan Teramai";
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
    // Array untuk menyimpan jalur sementara
    string rute[100]; // Asumsikan maksimal panjang jalur adalah 100
    int index = 0;

    adrVertex cariAwalan = findVertex(G, startPoint);
    adrVertex cariAkhir = findVertex(G, endPoint);

    if (cariAwalan == NULL && cariAkhir == NULL){
        cout << "Lokasi awal dan lokasi akhir yang anda masukkan tidak ditemukan" << endl;
    } else if (cariAwalan == NULL && cariAkhir != NULL){
        cout << "Lokasi awal yang anda masukkan tidak di temukan" << endl;
    } else if (cariAwalan != NULL && cariAkhir == NULL){
        cout << "Lokasi akhir yang anda masukkan tidak di temukan" << endl;
    } else {
        findRoutes(G, startPoint, endPoint, rute, index);
    }
}

void findRoutes(graph G, string awal, string akhir, string rute[], int &index) {
    // fungsi rekursif untuk mencari semua rute
    rute[index] = awal;
    index++;

    // Jika gedung tujuan ditemukan, cetak rute
    if (awal == akhir) {
        for (int i = 0; i < index; i++) {
            cout << rute[i];
            if (i < index - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        // Rekursif untuk semua edge yang keluar dari current
        adrVertex currentVertex = findVertex(G, awal);
        if (currentVertex != NULL) {
            adrEdge edge = firstEdge(currentVertex);
            while (edge != NULL) {
                string next = lokasiTujuan(edge);

                // Cek apakah sudah ada di jalur untuk menghindari siklus
                bool alreadyInPath = false;
                for (int i = 0; i < index; i++) {
                    if (rute[i] == next) {
                        alreadyInPath = true;
                        break;
                    }
                }

                // Jika belum ada di jalur, lanjutkan pencarian
                if (!alreadyInPath) {
                    findRoutes(G, next, akhir, rute, index);
                }

                edge = nextEdge(edge);
            }
        }
    }

    // Backtracking: hapus current dari path
    index--;
}
