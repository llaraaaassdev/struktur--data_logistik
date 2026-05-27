#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

struct Riwayat {

    string keterangan;
    Riwayat* next;
};

struct Paket {

    string resi;
    string asal;
    string tujuan;
    string posisi;

    Riwayat* head;
    Riwayat* tail;
};

struct Jalur {

    string kota;
    int jarak;
};

map<string, vector<Jalur> > rute;

map<string, queue<Paket*> > gudang;

map<string, Paket*> dataPaket;

void tambahRiwayat(Paket* p, string teks) {

    Riwayat* baru = new Riwayat();

    baru->keterangan = teks;
    baru->next = NULL;

    if(p->head == NULL) {

        p->head = baru;
        p->tail = baru;

    } else {

        p->tail->next = baru;
        p->tail = baru;
    }
}

void buatRute() {

    Jalur a;
    a.kota = "Bekasi";
    a.jarak = 20;
    rute["Jakarta"].push_back(a);

    Jalur b;
    b.kota = "Karawang";
    b.jarak = 35;
    rute["Bekasi"].push_back(b);

    Jalur c;
    c.kota = "Purwakarta";
    c.jarak = 60;
    rute["Karawang"].push_back(c);

    Jalur d;
    d.kota = "Bandung";
    d.jarak = 70;
    rute["Purwakarta"].push_back(d);

    Jalur e;
    e.kota = "Sumedang";
    e.jarak = 45;
    rute["Bandung"].push_back(e);

    Jalur f;
    f.kota = "Cirebon";
    f.jarak = 90;
    rute["Sumedang"].push_back(f);
}

void tambahPaket() {

    Paket* p = new Paket();

    cout << "\nTambah Paket\n";

    cout << "Resi : ";
    cin >> p->resi;

    if(dataPaket.find(p->resi)
       != dataPaket.end()) {

        cout << "Resi sudah ada\n";
        return;
    }

    cout << "Asal : ";
    cin >> p->asal;

    cout << "Tujuan : ";
    cin >> p->tujuan;

    p->posisi = p->asal;

    p->head = NULL;
    p->tail = NULL;

    tambahRiwayat(
        p,
        "Paket masuk gudang " + p->asal
    );

    gudang[p->asal].push(p);

    dataPaket[p->resi] = p;

    cout << "Paket berhasil ditambah\n";
}

void lihatGudang() {

    cout << "\nData Antrean\n";

    map<string, queue<Paket*> >::iterator it;

    for(it = gudang.begin();
        it != gudang.end();
        it++) {

        cout << "\nKota : "
             << it->first
             << endl;

        queue<Paket*> temp = it->second;

        if(temp.empty()) {

            cout << "Kosong\n";
        }

        while(!temp.empty()) {

            Paket* p = temp.front();

            cout << "Resi : "
                 << p->resi
                 << endl;

            cout << "Tujuan : "
                 << p->tujuan
                 << endl;

            temp.pop();
        }
    }
}

void kirimPaket() {

    string kota;

    cout << "\nKirim dari kota : ";
    cin >> kota;

    if(gudang[kota].empty()) {

        cout << "Tidak ada paket\n";
        return;
    }

    Paket* p = gudang[kota].front();

    gudang[kota].pop();

    if(p->posisi == p->tujuan) {

        cout << "Paket sudah sampai\n";
        return;
    }

    int i;

    for(i = 0;
        i < rute[p->posisi].size();
        i++) {

        string tujuanBaru =
            rute[p->posisi][i].kota;

        int jarak =
            rute[p->posisi][i].jarak;

        p->posisi = tujuanBaru;

        ostringstream oss;
        oss << jarak;

        tambahRiwayat(
            p,
            "Pindah ke "
            + tujuanBaru
            + " "
            + oss.str()
            + " km"
        );

        gudang[tujuanBaru].push(p);

        cout << "\nPaket dikirim ke "
             << tujuanBaru
             << endl;

        break;
    }

    if(p->posisi == p->tujuan) {

        tambahRiwayat(
            p,
            "Paket sudah sampai"
        );

        cout << "Paket tiba di tujuan\n";
    }
}

void cekPaket() {

    string cari;

    cout << "\nCari Resi : ";
    cin >> cari;

    if(dataPaket.find(cari)
       == dataPaket.end()) {

        cout << "Resi tidak ada\n";
        return;
    }

    Paket* p = dataPaket[cari];

    cout << "\nData Paket\n";

    cout << "Resi : "
         << p->resi
         << endl;

    cout << "Asal : "
         << p->asal
         << endl;

    cout << "Tujuan : "
         << p->tujuan
         << endl;

    cout << "Posisi : "
         << p->posisi
         << endl;

    cout << "\nRiwayat\n";

    Riwayat* bantu = p->head;

    int no = 1;

    while(bantu != NULL) {

        cout << no
             << ". "
             << bantu->keterangan
             << endl;

        bantu = bantu->next;

        no++;
    }
}

void lihatRute() {

    cout << "\nDaftar Rute\n";

    map<string, vector<Jalur> >::iterator kota;

    for(kota = rute.begin();
        kota != rute.end();
        kota++) {

        cout << kota->first
             << " -> ";

        int i;

        for(i = 0;
            i < kota->second.size();
            i++) {

            cout << kota->second[i].kota
                 << " ";
        }

        cout << endl;
    }
}

int main() {

    buatRute();

    int pilih;

    do {

        cout << "\n===== MENU =====\n";

        cout << "1. Tambah Paket\n";
        cout << "2. Kirim Paket\n";
        cout << "3. Lihat Gudang\n";
        cout << "4. Cek Paket\n";
        cout << "5. Lihat Rute\n";
        cout << "6. Keluar\n";

        cout << "Pilih : ";
        cin >> pilih;

        switch(pilih) {

            case 1:
                tambahPaket();
                break;

            case 2:
                kirimPaket();
                break;

            case 3:
                lihatGudang();
                break;

            case 4:
                cekPaket();
                break;

            case 5:
                lihatRute();
                break;

            case 6:
                cout << "Program selesai\n";
                break;

            default:
                cout << "Menu tidak ada\n";
        }

    } while(pilih != 6);

    return 0;
}
