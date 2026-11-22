#pragma once

#include <string>

using namespace std;

struct Organisasi {
    string kodeOrganisasi;
    string namaOrganisasi;
};

struct AnggotaNegara {
    string kodeNegara;
    string namaNegara;
    int tahunBergabung;
};

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

AdrOrganisasi createParent(const InfoOrganisasi& info);
void insertParent(ListOrganisasi& list, AdrOrganisasi parent);
AdrOrganisasi deleteParent(ListOrganisasi& list, const string& kode);
AdrOrganisasi findParent(const ListOrganisasi& list, const string& kode);
void printParent(const ListOrganisasi& list);

AdrAnggota createChild(const InfoAnggota& info);
void insertChild(ElmOrganisasi& parent, AdrAnggota child);
AdrAnggota deleteChild(ElmOrganisasi& parent, const string& kode);
AdrAnggota findChild(const ElmOrganisasi& parent, const string& kode);
void printChild(const ElmOrganisasi& parent);

void printAll(const ListOrganisasi& list);

void destroyParent(AdrOrganisasi parent) noexcept;
