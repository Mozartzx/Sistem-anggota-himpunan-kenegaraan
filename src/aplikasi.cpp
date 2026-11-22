#include "aplikasi.hpp"

#include <istream>
#include <ostream>
#include <sstream>

namespace {

bool bacaTeks(std::istream& in, std::ostream& out, const char* label, std::string& hasil) {
    while (true) {
        out << label << ": " << std::flush;
        if (!std::getline(in, hasil)) {
            return false;
        }
        const auto awal = hasil.find_first_not_of(" \t\r");
        if (awal != std::string::npos) {
            hasil = hasil.substr(awal, hasil.find_last_not_of(" \t\r") - awal + 1);
            return true;
        }
        out << "Masukan tidak boleh kosong.\n";
    }
}

bool bacaAngka(std::istream& in, std::ostream& out, const char* label, int& hasil) {
    std::string teks;
    while (bacaTeks(in, out, label, teks)) {
        std::istringstream parser(teks);
        std::string sisa;
        if ((parser >> hasil) && !(parser >> sisa)) {
            return true;
        }
        out << "Masukkan bilangan bulat.\n";
    }
    return false;
}

} // namespace

void Aplikasi::jalankan(std::istream& in, std::ostream& out, bool demo) {
    out << "Sistem Anggota Himpunan Kenegaraan\n";
    if (demo) {
        isiDataContoh();
        out << "Data demo dimuat.\n";
    }

    int pilihan;
    do {
        tampilkanMenu(out);
        if (!bacaAngka(in, out, "Pilihan", pilihan) ||
            !prosesPilihan(pilihan, in, out)) {
            break;
        }
    } while (true);

    out << "Program selesai.\n";
}

void Aplikasi::tampilkanMenu(std::ostream& out) const {
    out << "\n1. Tambah organisasi\n"
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

bool Aplikasi::prosesPilihan(int pilihan, std::istream& in, std::ostream& out) {
    if (pilihan == 0) {
        return false;
    }
    if (pilihan == 4) {
        sistem.tampilkanOrganisasi(out);
        return true;
    }
    if (pilihan == 9) {
        sistem.tampilkanSemua(out);
        return true;
    }
    if (pilihan < 1 || pilihan > 9) {
        out << "Pilihan tidak tersedia.\n";
        return true;
    }

    Organisasi organisasi;
    if (!bacaTeks(in, out, "Kode organisasi", organisasi.kodeOrganisasi)) {
        return false;
    }
    const std::string kode = organisasi.kodeOrganisasi;

    if (pilihan == 1) {
        if (!bacaTeks(in, out, "Nama organisasi", organisasi.namaOrganisasi)) {
            return false;
        }
        out << (sistem.tambahOrganisasi(organisasi)
                    ? "Organisasi ditambahkan.\n"
                    : "Kode organisasi sudah terdaftar.\n");
        return true;
    }
    if (!sistem.cariOrganisasi(kode, organisasi)) {
        out << "Organisasi tidak ditemukan.\n";
        return true;
    }
    if (pilihan == 8) {
        out << '[' << kode << "] " << organisasi.namaOrganisasi << '\n';
        sistem.tampilkanAnggota(kode, out);
        return true;
    }
    if (pilihan == 2) {
        sistem.hapusOrganisasi(kode);
        out << "Organisasi dan seluruh anggotanya dihapus.\n";
        return true;
    }
    if (pilihan == 3) {
        out << "Organisasi ditemukan: [" << kode << "] " << organisasi.namaOrganisasi << '\n';
        return true;
    }

    AnggotaNegara anggota{};
    if (!bacaTeks(in, out, "Kode negara", anggota.kodeNegara)) {
        return false;
    }
    if (pilihan == 5) {
        if (!bacaTeks(in, out, "Nama negara", anggota.namaNegara) ||
            !bacaAngka(in, out, "Tahun bergabung", anggota.tahunBergabung)) {
            return false;
        }
        if (anggota.tahunBergabung <= 0) {
            out << "Tahun bergabung harus lebih dari nol.\n";
        } else {
            out << (sistem.tambahAnggota(kode, anggota)
                        ? "Anggota ditambahkan.\n"
                        : "Negara sudah terdaftar pada organisasi ini.\n");
        }
        return true;
    }
    if (pilihan == 6) {
        out << (sistem.hapusAnggota(kode, anggota.kodeNegara)
                    ? "Anggota dihapus.\n"
                    : "Anggota tidak ditemukan.\n");
        return true;
    }

    if (sistem.cariAnggota(kode, anggota.kodeNegara, anggota)) {
        out << "Anggota ditemukan: [" << anggota.kodeNegara << "] " << anggota.namaNegara
            << " | Tahun bergabung: " << anggota.tahunBergabung << '\n';
    } else {
        out << "Anggota tidak ditemukan.\n";
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
