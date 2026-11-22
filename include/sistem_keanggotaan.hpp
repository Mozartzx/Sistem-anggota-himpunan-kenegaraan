#pragma once

#include "mll.hpp"

class SistemKeanggotaan {
public:
    SistemKeanggotaan() = default;
    ~SistemKeanggotaan();

    SistemKeanggotaan(const SistemKeanggotaan&) = delete;
    SistemKeanggotaan& operator=(const SistemKeanggotaan&) = delete;

    bool tambahOrganisasi(const Organisasi& info);
    bool hapusOrganisasi(const string& kode);
    bool cariOrganisasi(const string& kode, Organisasi& hasil) const;
    void tampilkanOrganisasi() const;

    bool tambahAnggota(const string& kodeOrganisasi, const AnggotaNegara& info);
    bool hapusAnggota(const string& kodeOrganisasi, const string& kodeNegara);
    bool cariAnggota(const string& kodeOrganisasi, const string& kodeNegara,
                     AnggotaNegara& hasil) const;
    bool tampilkanAnggota(const string& kodeOrganisasi) const;
    void tampilkanSemua() const;

private:
    ListOrganisasi organisasi;
};
