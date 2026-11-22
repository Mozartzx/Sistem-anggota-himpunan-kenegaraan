#include "aplikasi.hpp"

#include <iostream>
#include <sstream>

namespace {

bool bacaTeks(istream& in, const char* label, string& hasil) {
    while (true) {
        cout << label << ": " << flush;
        if (!getline(in, hasil)) {
            return false;
        }
        const auto awal = hasil.find_first_not_of(" \t\r");
        if (awal != string::npos) {
            hasil = hasil.substr(awal, hasil.find_last_not_of(" \t\r") - awal + 1);
            return true;
        }
        cout << "Masukan tidak boleh kosong.\n";
    }
}

bool bacaAngka(istream& in, const char* label, int& hasil) {
    string teks;
    while (bacaTeks(in, label, teks)) {
        istringstream parser(teks);
        string sisa;
        if ((parser >> hasil) && !(parser >> sisa)) {
            return true;
        }
        cout << "Masukkan bilangan bulat.\n";
    }
    return false;
}

}

void Aplikasi::jalankan(istream& in, bool demo) {
    cout << "Sistem Anggota Himpunan Kenegaraan\n";
    if (demo) {
        isiDataContoh();
        cout << "Data demo dimuat.\n";
    }

    int pilihan;
    do {
        tampilkanMenu();
        if (!bacaAngka(in, "Pilihan", pilihan) ||
            !prosesPilihan(pilihan, in)) {
            break;
        }
    } while (true);

    cout << "Program selesai.\n";
}

void Aplikasi::tampilkanMenu() const {
    cout << "\n1. Tambah organisasi\n"
         << "2. Hapus organisasi\n"
         << "3. Cari organisasi\n"
         << "4. Tampilkan semua organisasi\n"
         << "5. Tambah anggota ke organisasi\n"
         << "6. Hapus anggota dari organisasi\n"
         << "7. Cari anggota dalam organisasi\n"
         << "8. Tampilkan anggota suatu organisasi\n"
         << "9. Tampilkan seluruh struktur\n"
         << "0. Keluar\n";
}

bool Aplikasi::prosesPilihan(int pilihan, istream& in) {
    if (pilihan == 0) {
        return false;
    }
    if (pilihan == 4) {
        sistem.tampilkanOrganisasi();
        return true;
    }
    if (pilihan == 9) {
        sistem.tampilkanSemua();
        return true;
    }
    if (pilihan < 1 || pilihan > 9) {
        cout << "Pilihan tidak tersedia.\n";
        return true;
    }

    Organisasi organisasi;
    if (!bacaTeks(in, "Kode organisasi", organisasi.kodeOrganisasi)) {
        return false;
    }
    const string kode = organisasi.kodeOrganisasi;

    if (pilihan == 1) {
        if (!bacaTeks(in, "Nama organisasi", organisasi.namaOrganisasi)) {
            return false;
        }
        cout << (sistem.tambahOrganisasi(organisasi)
                    ? "Organisasi ditambahkan.\n"
                    : "Kode organisasi sudah terdaftar.\n");
        return true;
    }
    if (!sistem.cariOrganisasi(kode, organisasi)) {
        cout << "Organisasi tidak ditemukan.\n";
        return true;
    }
    if (pilihan == 8) {
        cout << '[' << kode << "] " << organisasi.namaOrganisasi << '\n';
        sistem.tampilkanAnggota(kode);
        return true;
    }
    if (pilihan == 2) {
        sistem.hapusOrganisasi(kode);
        cout << "Organisasi dan seluruh anggotanya dihapus.\n";
        return true;
    }
    if (pilihan == 3) {
        cout << "Organisasi ditemukan: [" << kode << "] " << organisasi.namaOrganisasi << '\n';
        return true;
    }

    AnggotaNegara anggota{};
    if (!bacaTeks(in, "Kode negara", anggota.kodeNegara)) {
        return false;
    }
    if (pilihan == 5) {
        if (!bacaTeks(in, "Nama negara", anggota.namaNegara) ||
            !bacaAngka(in, "Tahun bergabung", anggota.tahunBergabung)) {
            return false;
        }
        if (anggota.tahunBergabung <= 0) {
            cout << "Tahun bergabung harus lebih dari nol.\n";
        } else {
            cout << (sistem.tambahAnggota(kode, anggota)
                        ? "Anggota ditambahkan.\n"
                        : "Negara sudah terdaftar pada organisasi ini.\n");
        }
        return true;
    }
    if (pilihan == 6) {
        cout << (sistem.hapusAnggota(kode, anggota.kodeNegara)
                    ? "Anggota dihapus.\n"
                    : "Anggota tidak ditemukan.\n");
        return true;
    }

    if (sistem.cariAnggota(kode, anggota.kodeNegara, anggota)) {
        cout << "Anggota ditemukan: [" << anggota.kodeNegara << "] " << anggota.namaNegara
             << " | Tahun bergabung: " << anggota.tahunBergabung << '\n';
    } else {
        cout << "Anggota tidak ditemukan.\n";
    }
    return true;
}

void Aplikasi::isiDataContoh() {
    sistem.tambahOrganisasi({"ASEAN", "Perhimpunan Bangsa-Bangsa Asia Tenggara"});
    sistem.tambahAnggota("ASEAN", {"IDN", "Indonesia", 1967});
    sistem.tambahAnggota("ASEAN", {"MYS", "Malaysia", 1967});
    sistem.tambahAnggota("ASEAN", {"PHL", "Filipina", 1967});
    sistem.tambahAnggota("ASEAN", {"SGP", "Singapura", 1967});
    sistem.tambahAnggota("ASEAN", {"THA", "Thailand", 1967});

    sistem.tambahOrganisasi({"PBB", "Perserikatan Bangsa-Bangsa"});
    sistem.tambahAnggota("PBB", {"IDN", "Indonesia", 1950});
    sistem.tambahAnggota("PBB", {"MYS", "Malaysia", 1957});
    sistem.tambahAnggota("PBB", {"JPN", "Jepang", 1956});
    sistem.tambahAnggota("PBB", {"CAN", "Kanada", 1945});
    sistem.tambahAnggota("PBB", {"AUS", "Australia", 1945});

    sistem.tambahOrganisasi({"OPEC", "Organisasi Negara-Negara Pengekspor Minyak"});
    sistem.tambahAnggota("OPEC", {"IRN", "Iran", 1960});
    sistem.tambahAnggota("OPEC", {"IRQ", "Irak", 1960});
    sistem.tambahAnggota("OPEC", {"KWT", "Kuwait", 1960});
    sistem.tambahAnggota("OPEC", {"SAU", "Arab Saudi", 1960});
    sistem.tambahAnggota("OPEC", {"VEN", "Venezuela", 1960});
}
