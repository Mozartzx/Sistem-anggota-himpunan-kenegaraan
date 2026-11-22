#include "mll.hpp"

#include <iostream>

AdrOrganisasi createParent(const InfoOrganisasi& info) {
    return new ElmOrganisasi{info, nullptr, {}};
}

void insertParent(ListOrganisasi& list, AdrOrganisasi parent) {
    if (list.first == nullptr) {
        list.first = parent;
        return;
    }

    AdrOrganisasi terakhir = list.first;
    while (terakhir->next != nullptr) {
        terakhir = terakhir->next;
    }
    terakhir->next = parent;
}

AdrOrganisasi deleteParent(ListOrganisasi& list, const string& kode) {
    AdrOrganisasi sebelum = nullptr;
    AdrOrganisasi saatIni = list.first;
    while (saatIni != nullptr && saatIni->info.kodeOrganisasi != kode) {
        sebelum = saatIni;
        saatIni = saatIni->next;
    }
    if (saatIni == nullptr) {
        return nullptr;
    }

    if (sebelum == nullptr) {
        list.first = saatIni->next;
    } else {
        sebelum->next = saatIni->next;
    }
    saatIni->next = nullptr;
    return saatIni;
}

AdrOrganisasi findParent(const ListOrganisasi& list, const string& kode) {
    AdrOrganisasi parent = list.first;
    while (parent != nullptr && parent->info.kodeOrganisasi != kode) {
        parent = parent->next;
    }
    return parent;
}

void printParent(const ListOrganisasi& list) {
    if (list.first == nullptr) {
        cout << "Belum ada organisasi.\n";
        return;
    }

    for (const ElmOrganisasi* parent = list.first; parent != nullptr; parent = parent->next) {
        cout << '[' << parent->info.kodeOrganisasi << "] "
             << parent->info.namaOrganisasi << '\n';
    }
}

AdrAnggota createChild(const InfoAnggota& info) {
    return new ElmAnggota{info, nullptr};
}

void insertChild(ElmOrganisasi& parent, AdrAnggota child) {
    if (parent.anggota.first == nullptr) {
        parent.anggota.first = child;
        return;
    }

    AdrAnggota terakhir = parent.anggota.first;
    while (terakhir->next != nullptr) {
        terakhir = terakhir->next;
    }
    terakhir->next = child;
}

AdrAnggota deleteChild(ElmOrganisasi& parent, const string& kode) {
    AdrAnggota sebelum = nullptr;
    AdrAnggota saatIni = parent.anggota.first;
    while (saatIni != nullptr && saatIni->info.kodeNegara != kode) {
        sebelum = saatIni;
        saatIni = saatIni->next;
    }
    if (saatIni == nullptr) {
        return nullptr;
    }

    if (sebelum == nullptr) {
        parent.anggota.first = saatIni->next;
    } else {
        sebelum->next = saatIni->next;
    }
    saatIni->next = nullptr;
    return saatIni;
}

AdrAnggota findChild(const ElmOrganisasi& parent, const string& kode) {
    AdrAnggota child = parent.anggota.first;
    while (child != nullptr && child->info.kodeNegara != kode) {
        child = child->next;
    }
    return child;
}

void printChild(const ElmOrganisasi& parent) {
    if (parent.anggota.first == nullptr) {
        cout << "  Belum ada anggota.\n";
        return;
    }

    for (const ElmAnggota* child = parent.anggota.first; child != nullptr; child = child->next) {
        cout << "  - [" << child->info.kodeNegara << "] " << child->info.namaNegara
             << " | Tahun bergabung: " << child->info.tahunBergabung << '\n';
    }
}

void printAll(const ListOrganisasi& list) {
    if (list.first == nullptr) {
        printParent(list);
        return;
    }

    for (const ElmOrganisasi* parent = list.first; parent != nullptr; parent = parent->next) {
        cout << '[' << parent->info.kodeOrganisasi << "] "
             << parent->info.namaOrganisasi << '\n';
        printChild(*parent);
    }
}

void destroyParent(AdrOrganisasi parent) noexcept {
    while (parent->anggota.first != nullptr) {
        AdrAnggota child = parent->anggota.first;
        parent->anggota.first = child->next;
        child->next = nullptr;
        delete child;
    }
    delete parent;
}
