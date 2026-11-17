// NIM      : 123250107
// Nama     : Olivia Putri Azzahra

#include <iostream>
using namespace std;

struct nodeQueue {
    int kode;
    string nama;
    nodeQueue* next;
};

struct nodeStack {
    int kode;
    string nama;
    nodeStack* next;
};

struct nodeTree {
    int kode;
    string nama;
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* front = nullptr;
nodeQueue* last = nullptr;
nodeQueue* simpan = nullptr;
nodeStack* top = nullptr;
nodeTree* root = nullptr;

nodeTree* tambah_tree(nodeTree* akar, int kode, string nama) {
    if (akar == nullptr) {
        return new nodeTree {kode, nama, nullptr, nullptr};
    }
    if (kode < akar->kode) {
        akar->kiri = tambah_tree(akar->kiri, kode, nama);
    } 
    if (kode > akar->kode) {
        akar->kanan = tambah_tree(akar->kanan, kode, nama);
    }
    return akar;
}

nodeTree* cari_tree(nodeTree* akar, int kode){
    if (akar == nullptr || akar->kode == kode){
        return akar;
    }
    if (kode < akar->kode){
        return cari_tree(akar->kiri, kode);
    }
    return cari_tree(akar->kanan, kode);
}

nodeTree* hapus_tree(nodeTree* akar, int kode) {
    if (akar == nullptr){
        return nullptr;
    }
    if (kode < akar->kode){
        akar->kiri = hapus_tree(akar->kiri, kode);
    } else if (kode > akar->kode){
        akar->kanan = hapus_tree(akar->kanan, kode);
    } else if (akar->kiri == nullptr){
        nodeTree* sisa = akar->kanan;
        delete akar;
        return sisa;
    } else if (akar->kanan == nullptr){
        nodeTree* sisa = akar->kiri;
        delete akar;
        return sisa;
    } else {
        nodeTree* pengganti = akar->kanan;
        while (pengganti->kiri){
            pengganti = pengganti->kiri;
        }
        akar->kode = pengganti->kode;
        akar->nama = pengganti->nama;
        akar->kanan = hapus_tree(akar->kanan, pengganti->kode);
    }
    return akar;
}

void preOrder (nodeTree* akar, int& no) {
    if (akar == nullptr){
        return;
    }

    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
    preOrder(akar->kiri, no);
    preOrder(akar->kanan, no);
}

void inOrder(nodeTree* akar, int& no){
    if (akar == nullptr){
        return;
    }

    inOrder(akar->kiri, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
    inOrder(akar->kanan, no);
}

void postOrder(nodeTree* akar, int& no){
    if (akar == nullptr){
        return;
    }

    postOrder(akar->kiri, no);
    postOrder(akar->kanan, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
}

// fungsi utama
void tambah_energi() {
    int kode;
    string nama;

    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus lebih dari 0.";
        return;
    }

    nodeQueue* q = front;
    while(q != nullptr) {
        if (q->kode == kode) {
            cout << "Kode Energi sudah digunakan.\n\n";
            return;
        }
        q = q->next;
    }

    nodeStack* s = top;
    while (s != nullptr) {
        if (s->kode == kode) {
            cout << "Kode Energi sudah digunakan.\n\n";
            return;
        }
        s = s->next;
    }

    cout << "Masukkan nama energi: ";
    cin.ignore();
    getline(cin, nama);
    if (nama.empty()) {
        cout << "Nama energi tidak boleh kosong.\n\n";
        return;
    }

    nodeQueue* nb = new nodeQueue {kode, nama, nullptr};
    if (front == nullptr) {
        front = last = nb;
    } else {
        last->next = nb;
        last = nb;
    }

    cout << "berhasil menambahkan energi.\n\n";
}

void lihat_antrean() {
    if (front == nullptr){
        cout << "Antrean Nergi masih kosong.\n\n";
        return;
    }

    cout << "=== Energi Dalam Antrean ===\n\n";
    nodeQueue* nb = front;
    int no = 1;
    while (nb != nullptr){
        cout << no << ". [" << nb->kode << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

void proses_energi() {
    if (top == nullptr){
        cout << "Antrean Energi masih kosong.\n\n";
        return;
    }

    nodeQueue* hapus = front;
    nodeStack* nb = new nodeStack {hapus->kode, hapus->nama, top};
    top = nb;
    root = tambah_tree(root, hapus->kode, hapus->nama);
    cout << "Berhasil memproses energi " << hapus->nama << "!\n\n";
    front = hapus->next;

    if (front == nullptr){
        last = nullptr;
    }
    delete hapus;
}

void energi_terserap() {
    if (front == nullptr){
        last = nullptr;
    }

    cout << "=== Energi Yang Sudah Terserap ===\n\n";
    nodeQueue* nb = front;
    int no = 1;
    while (nb != nullptr){
        cout << no << ". [" << nb->kode << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

void riwayat_teratas() {
    if (top == nullptr){
        cout << "Antrean Energi masih kosong.\n\n";
        return;
    }

    nodeStack* nb = top;
    top = nb->next;
    cout << "Riwayat Eenrgi " << nb->nama << "teratas telah dihapus.";
    delete nb; 
}

void cari_energi() {
    if (root == nullptr) {
        cout << "Energi masih kosong.\n\n";
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;

    if (cin.fail() || kode <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus lebih dari 0.";
        return;
    }

    nodeTree* hasil = cari_tree(root, kode);
    if (hasil == nullptr){
        cout << "Energi dengan kode [" << kode << "] tidak ditemukan.\n\n";
        return;
    }
    cout << "Ditemukan: [" << hasil->kode << "] " << hasil->nama << endl;
}

void lihat_isi(){
    if (root == nullptr) {
        cout << "Energi masih kosong.\n\n";
        return;
    }

    int pil;
    int no = 1;

    cout << "=== Isi Kristal Organ ===\n\n";
    cout << "1. Pre-Order \n2. In-Order \n3. Post-Order \n\n";
    cout << "Masukkan pilihan Anda: ";
    cin >> pil;
    if (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan harus dari 1 sampai 3.";
        return;
    }
    cout << endl;

    switch (pil){
        case 1: {
            preOrder(root, no);
            break;
        }
        case 2: {
            inOrder(root, no);
            break;
        }
        case 3: {
            postOrder(root, no);
            break;
        }
        default: {
            cout << "Pilihan yang Anda masukkan salah.";
        }
    }
    cout << endl;
}

void gunakan_energi(){
    if (root == nullptr) {
        cout << "Energi masih kosong.\n\n";
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus lebih dari 0.";
        return;
    }

    nodeTree* hasil = cari_tree(root, kode);
    if (hasil == nullptr){
        cout << "Energi dengan kode [" << hasil->kode << "] tidak ditemukan.\n\n";
        return;
    }
    cout << "Energi " << hasil->nama << "telah digunakan!\n\n";
    root = hapus_tree(root, kode);
}

int main() {
    int pilih;
    while (pilih != 9) {
        cout << "===== SISTEM ORGAN INTI NIRWANA =====\n\n";
        cout << "1. Tambah Energi \n2. Lihat Energi Dalam Antrean\n";
        cout << "3. Proses Energi \n4. Lihat Energi Yang Sudah Terserap\n";
        cout << "5. Hapus Riwayat Energi Teratas \n6. Cari Energi Di Organ\n";
        cout << "7. Lihat Isi Organ \n8. Gunakan Energi \n9. Keluar \n\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilih;

        if (cin.fail() || pilih > 9) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "pilih 1-9";
            continue;
        }

        switch (pilih) {
            case 1: {
                char ulang = 'y';
                while (ulang == 'y' || ulang == 'Y'){
                    tambah_energi();
                    cout << "Apakah Anda ingin menambahkan energi lagi? (y/n): ";
                    cin >> ulang;
                    cout << endl;
                }
                break;
            }
            case 2: {
                lihat_antrean();
                break;
            }
            case 3: {
                proses_energi();
                break;
            }
            case 4: {
                energi_terserap();
                break;
            }
            case 5: {
                riwayat_teratas();
                break;
            }
            case 6: {
                cari_energi();
                break;
            }
            case 7: {
                lihat_isi();
                break;
            }
            case 8: {
                gunakan_energi();
                break;
            }
            case 9: {
                cout << "Terima kasih.";
                exit(0);
            }
            default: {
                cout << "pilihan yang Anda masukkan salah." << endl;
            }
        }
    }
}