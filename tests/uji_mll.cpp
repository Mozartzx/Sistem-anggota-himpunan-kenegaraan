#include "sistem_keanggotaan.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {

void pastikan(bool kondisi, const char* pesan) {
    if (!kondisi) {
        throw runtime_error(pesan);
    }
}

void ujiParent(ostringstream& output) {
    SistemKeanggotaan sistem;
    Organisasi hasil;

    pastikan(!sistem.cariOrganisasi("A", hasil), "Pencarian pada list parent kosong");
    pastikan(!sistem.hapusOrganisasi("A"), "Penghapusan pada list parent kosong");
    sistem.tampilkanOrganisasi();
    pastikan(output.str() == "Belum ada organisasi.\n", "Cetak list parent kosong");

    pastikan(!sistem.tambahOrganisasi({"", "Organisasi A"}), "Tolak kode parent kosong");
    pastikan(sistem.tambahOrganisasi({"A", "Organisasi A"}), "Tambah parent pertama");
    pastikan(sistem.cariOrganisasi("A", hasil) && hasil.namaOrganisasi == "Organisasi A",
             "Temukan parent pertama");
    pastikan(!sistem.tambahOrganisasi({"A", "Nama lain"}), "Tolak kode parent duplikat");
    pastikan(sistem.tambahOrganisasi({"B", "Organisasi B"}), "Tambah parent kedua");
    pastikan(sistem.tambahOrganisasi({"C", "Organisasi C"}), "Tambah parent ketiga");
    pastikan(sistem.tambahOrganisasi({"D", "Organisasi D"}), "Tambah parent keempat");
    pastikan(!sistem.cariOrganisasi("Z", hasil), "Parent yang tidak ada tidak ditemukan");

    output.str("");
    sistem.tampilkanOrganisasi();
    pastikan(output.str() == "[A] Organisasi A\n[B] Organisasi B\n[C] Organisasi C\n[D] Organisasi D\n",
             "Traversal parent sesuai urutan penambahan");

    pastikan(sistem.hapusOrganisasi("B"), "Hapus parent tengah");
    pastikan(!sistem.cariOrganisasi("B", hasil), "Parent tengah sudah lepas");
    pastikan(sistem.hapusOrganisasi("D"), "Hapus parent ekor");
    pastikan(sistem.hapusOrganisasi("A"), "Hapus parent kepala");
    pastikan(sistem.cariOrganisasi("C", hasil), "Parent sisa tetap terhubung");
    pastikan(sistem.hapusOrganisasi("C"), "Hapus satu-satunya parent tersisa");

    output.str("");
    sistem.tampilkanSemua();
    pastikan(output.str() == "Belum ada organisasi.\n", "List utama kembali kosong");
}

void ujiChild(ostringstream& output) {
    SistemKeanggotaan sistem;
    AnggotaNegara hasil{};

    pastikan(sistem.tambahOrganisasi({"A", "Organisasi A"}), "Siapkan parent A");
    pastikan(!sistem.tambahAnggota("Z", {"X", "Negara X", 2000}), "Tolak parent yang tidak ada");
    pastikan(!sistem.tampilkanAnggota("Z"), "Cetak child parent yang tidak ada");
    pastikan(!sistem.tambahAnggota("A", {"X", "Negara X", 0}), "Tolak tahun nol");
    pastikan(!sistem.hapusAnggota("A", "X"), "Hapus pada list anak kosong");
    pastikan(!sistem.cariAnggota("A", "X", hasil), "Cari pada list anak kosong");
    pastikan(sistem.tampilkanAnggota("A") && output.str() == "  Belum ada anggota.\n",
             "Cetak list anak kosong");

    pastikan(sistem.tambahAnggota("A", {"X", "Negara X", 2000}), "Tambah anak pertama");
    pastikan(!sistem.tambahAnggota("A", {"X", "Nama lain", 2001}), "Tolak anak duplikat");
    pastikan(sistem.tambahAnggota("A", {"Y", "Negara Y", 2002}), "Tambah anak kedua");
    pastikan(sistem.tambahAnggota("A", {"Z", "Negara Z", 2003}), "Tambah anak ketiga");
    pastikan(sistem.tambahAnggota("A", {"W", "Negara W", 2004}), "Tambah anak keempat");
    pastikan(sistem.cariAnggota("A", "X", hasil) && hasil.tahunBergabung == 2000,
             "Pencarian anak mengembalikan data yang tepat");

    pastikan(sistem.hapusAnggota("A", "Y"), "Hapus anak tengah");
    pastikan(sistem.hapusAnggota("A", "W"), "Hapus anak ekor");
    pastikan(sistem.hapusAnggota("A", "X"), "Hapus anak kepala");
    pastikan(!sistem.cariAnggota("A", "X", hasil), "Anak yang dihapus tidak ditemukan");
    pastikan(!sistem.hapusAnggota("A", "X"), "Hapus anak yang sudah tidak ada");
    pastikan(sistem.cariAnggota("A", "Z", hasil), "Anak tersisa tetap terhubung");
    pastikan(sistem.hapusAnggota("A", "Z"), "Hapus satu-satunya anak tersisa");

    output.str("");
    pastikan(sistem.tampilkanAnggota("A") && output.str() == "  Belum ada anggota.\n",
             "List anak kembali kosong");
}

void ujiHubungan(ostringstream& output) {
    SistemKeanggotaan sistem;
    AnggotaNegara hasil{};

    pastikan(sistem.tambahOrganisasi({"A", "Organisasi A"}), "Siapkan parent A");
    pastikan(sistem.tambahOrganisasi({"B", "Organisasi B"}), "Siapkan parent B");
    pastikan(sistem.tambahAnggota("A", {"X", "Negara X", 2000}), "Negara X masuk A");
    pastikan(sistem.tambahAnggota("A", {"Y", "Negara Y", 2001}), "Negara Y masuk A");
    pastikan(sistem.tambahAnggota("B", {"X", "Negara X", 2002}), "Negara X juga boleh masuk B");

    sistem.tampilkanSemua();
    pastikan(output.str() ==
                 "[A] Organisasi A\n"
                 "  - [X] Negara X | Tahun bergabung: 2000\n"
                 "  - [Y] Negara Y | Tahun bergabung: 2001\n"
                 "[B] Organisasi B\n"
                 "  - [X] Negara X | Tahun bergabung: 2002\n",
             "Cetak seluruh struktur mengelompokkan child dengan benar");

    pastikan(sistem.hapusAnggota("A", "X"), "Hapus X dari A");
    pastikan(sistem.cariAnggota("B", "X", hasil) && hasil.tahunBergabung == 2002,
             "X tetap ada di B sesudah keluar dari A");
    pastikan(sistem.hapusOrganisasi("A"), "Hapus parent yang masih memiliki anak");
    pastikan(!sistem.cariAnggota("A", "Y", hasil), "Daftar anak A sudah tidak dapat diakses");
    pastikan(sistem.cariAnggota("B", "X", hasil), "B beserta anggotanya tetap utuh");
}

}

int main() {
    ostringstream output;
    streambuf* bufferAsli = cout.rdbuf(output.rdbuf());

    try {
        ujiParent(output);
        output.str("");
        ujiChild(output);
        output.str("");
        ujiHubungan(output);
    } catch (const exception& error) {
        cout.rdbuf(bufferAsli);
        cout << "GAGAL: " << error.what() << '\n';
        return 1;
    }

    cout.rdbuf(bufferAsli);
    cout << "LULUS: operasi parent dan urutan traversal\n";
    cout << "LULUS: operasi child dan kasus batas\n";
    cout << "LULUS: pemisahan keanggotaan dan cetak seluruh struktur\n";
}
