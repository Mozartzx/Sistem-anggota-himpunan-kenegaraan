#include "sistem_keanggotaan.hpp"

SistemKeanggotaan::~SistemKeanggotaan() {
    while (organisasi.first != nullptr) {
        AdrOrganisasi parent = deleteParent(
            organisasi, organisasi.first->info.kodeOrganisasi);
        destroyParent(parent);
    }
}

bool SistemKeanggotaan::tambahOrganisasi(const Organisasi& info) {
    if (info.kodeOrganisasi.empty() || info.namaOrganisasi.empty() ||
        findParent(organisasi, info.kodeOrganisasi) != nullptr) {
        return false;
    }

    AdrOrganisasi parent = createParent(info);
    insertParent(organisasi, parent);
    return true;
}

bool SistemKeanggotaan::hapusOrganisasi(const string& kode) {
    AdrOrganisasi parent = deleteParent(organisasi, kode);
    if (parent == nullptr) {
        return false;
    }

    destroyParent(parent);
    return true;
}

bool SistemKeanggotaan::cariOrganisasi(const string& kode, Organisasi& hasil) const {
    const ElmOrganisasi* parent = findParent(organisasi, kode);
    if (parent == nullptr) {
        return false;
    }
    hasil = parent->info;
    return true;
}

void SistemKeanggotaan::tampilkanOrganisasi() const {
    printParent(organisasi);
}

bool SistemKeanggotaan::tambahAnggota(const string& kodeOrganisasi,
                                    const AnggotaNegara& info) {
    AdrOrganisasi parent = findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr || info.kodeNegara.empty() || info.namaNegara.empty() ||
        info.tahunBergabung <= 0 || findChild(*parent, info.kodeNegara) != nullptr) {
        return false;
    }

    AdrAnggota child = createChild(info);
    insertChild(*parent, child);
    return true;
}

bool SistemKeanggotaan::hapusAnggota(const string& kodeOrganisasi,
                                   const string& kodeNegara) {
    AdrOrganisasi parent = findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr) {
        return false;
    }

    AdrAnggota child = deleteChild(*parent, kodeNegara);
    if (child == nullptr) {
        return false;
    }
    delete child;
    return true;
}

bool SistemKeanggotaan::cariAnggota(const string& kodeOrganisasi,
                                  const string& kodeNegara,
                                  AnggotaNegara& hasil) const {
    const ElmOrganisasi* parent = findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr) {
        return false;
    }

    const ElmAnggota* child = findChild(*parent, kodeNegara);
    if (child == nullptr) {
        return false;
    }
    hasil = child->info;
    return true;
}

bool SistemKeanggotaan::tampilkanAnggota(const string& kodeOrganisasi) const {
    const ElmOrganisasi* parent = findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr) {
        return false;
    }

    printChild(*parent);
    return true;
}

void SistemKeanggotaan::tampilkanSemua() const {
    printAll(organisasi);
}
