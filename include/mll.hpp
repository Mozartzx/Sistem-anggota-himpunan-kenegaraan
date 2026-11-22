#pragma once

#include <iosfwd>
#include <string>

struct Organisasi {
    std::string kodeOrganisasi;
    std::string namaOrganisasi;
};

struct AnggotaNegara {
    std::string kodeNegara;
    std::string namaNegara;
    int tahunBergabung;
};

namespace mll {

using InfoOrganisasi = Organisasi;
using InfoAnggota = AnggotaNegara;

struct ElmOrganisasi;
struct ElmAnggota;

using AdrOrganisasi = ElmOrganisasi*;
using AdrAnggota = ElmAnggota*;

struct ListAnggota {
    AdrAnggota first = nullptr;
};

struct ElmOrganisasi {
    InfoOrganisasi info;
    AdrOrganisasi next = nullptr;
    ListAnggota anggota;
};

struct ElmAnggota {
    InfoAnggota info;
    AdrAnggota next = nullptr;
};

struct ListOrganisasi {
    AdrOrganisasi first = nullptr;
};

// insert menerima node baru yang belum terhubung ke list mana pun.
// delete melepaskan node dan mengembalikan alamatnya ke pemanggil.
AdrOrganisasi createParent(const InfoOrganisasi& info);
void insertParent(ListOrganisasi& list, AdrOrganisasi parent);
AdrOrganisasi deleteParent(ListOrganisasi& list, const std::string& kode);
AdrOrganisasi findParent(const ListOrganisasi& list, const std::string& kode);
void printParent(const ListOrganisasi& list, std::ostream& out);

AdrAnggota createChild(const InfoAnggota& info);
void insertChild(ElmOrganisasi& parent, AdrAnggota child);
AdrAnggota deleteChild(ElmOrganisasi& parent, const std::string& kode);
AdrAnggota findChild(const ElmOrganisasi& parent, const std::string& kode);
void printChild(const ElmOrganisasi& parent, std::ostream& out);

void printAll(const ListOrganisasi& list, std::ostream& out);

// Parent harus sudah dilepas dari list. Child miliknya dibebaskan dahulu.
void destroyParent(AdrOrganisasi parent) noexcept;

} // namespace mll
