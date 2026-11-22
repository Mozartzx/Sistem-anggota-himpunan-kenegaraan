#include "sistem_keanggotaan.hpp"

SistemKeanggotaan::~SistemKeanggotaan() {
    while (organisasi.first != nullptr) {
        mll::AdrOrganisasi parent = mll::deleteParent(
            organisasi, organisasi.first->info.kodeOrganisasi);
        mll::destroyParent(parent);
    }
}

bool SistemKeanggotaan::tambahOrganisasi(const Organisasi& info) {
    if (info.kodeOrganisasi.empty() || info.namaOrganisasi.empty() ||
        mll::findParent(organisasi, info.kodeOrganisasi) != nullptr) {
        return false;
    }

    mll::AdrOrganisasi parent = mll::createParent(info);
    mll::insertParent(organisasi, parent);
    return true;
}

bool SistemKeanggotaan::hapusOrganisasi(const std::string& kode) {
    mll::AdrOrganisasi parent = mll::deleteParent(organisasi, kode);
    if (parent == nullptr) {
        return false;
    }

    mll::destroyParent(parent);
    return true;
}

bool SistemKeanggotaan::cariOrganisasi(const std::string& kode, Organisasi& hasil) const {
    const mll::ElmOrganisasi* parent = mll::findParent(organisasi, kode);
    if (parent == nullptr) {
        return false;
    }
    hasil = parent->info;
    return true;
}

void SistemKeanggotaan::tampilkanOrganisasi(std::ostream& out) const {
    mll::printParent(organisasi, out);
}

bool SistemKeanggotaan::tambahAnggota(const std::string& kodeOrganisasi,
                                    const AnggotaNegara& info) {
    mll::AdrOrganisasi parent = mll::findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr || info.kodeNegara.empty() || info.namaNegara.empty() ||
        info.tahunBergabung <= 0 || mll::findChild(*parent, info.kodeNegara) != nullptr) {
        return false;
    }

    mll::AdrAnggota child = mll::createChild(info);
    mll::insertChild(*parent, child);
    return true;
}

bool SistemKeanggotaan::hapusAnggota(const std::string& kodeOrganisasi,
                                   const std::string& kodeNegara) {
    mll::AdrOrganisasi parent = mll::findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr) {
        return false;
    }

    mll::AdrAnggota child = mll::deleteChild(*parent, kodeNegara);
    if (child == nullptr) {
        return false;
    }
    delete child;
    return true;
}

bool SistemKeanggotaan::cariAnggota(const std::string& kodeOrganisasi,
                                  const std::string& kodeNegara,
                                  AnggotaNegara& hasil) const {
    const mll::ElmOrganisasi* parent = mll::findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr) {
        return false;
    }

    const mll::ElmAnggota* child = mll::findChild(*parent, kodeNegara);
    if (child == nullptr) {
        return false;
    }
    hasil = child->info;
    return true;
}

bool SistemKeanggotaan::tampilkanAnggota(const std::string& kodeOrganisasi,
                                       std::ostream& out) const {
    const mll::ElmOrganisasi* parent = mll::findParent(organisasi, kodeOrganisasi);
    if (parent == nullptr) {
        return false;
    }

    mll::printChild(*parent, out);
    return true;
}

void SistemKeanggotaan::tampilkanSemua(std::ostream& out) const {
    mll::printAll(organisasi, out);
}
