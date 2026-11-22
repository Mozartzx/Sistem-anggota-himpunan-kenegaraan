#pragma once

#include "mll.hpp"

class SistemKeanggotaan {
public:
    SistemKeanggotaan() = default;
    ~SistemKeanggotaan();

    SistemKeanggotaan(const SistemKeanggotaan&) = delete;
    SistemKeanggotaan& operator=(const SistemKeanggotaan&) = delete;

    bool tambahOrganisasi(const Organisasi& info);
    bool hapusOrganisasi(const std::string& kode);
    bool cariOrganisasi(const std::string& kode, Organisasi& hasil) const;
    void tampilkanOrganisasi(std::ostream& out) const;

    bool tambahAnggota(const std::string& kodeOrganisasi, const AnggotaNegara& info);
    bool hapusAnggota(const std::string& kodeOrganisasi, const std::string& kodeNegara);
    bool cariAnggota(const std::string& kodeOrganisasi, const std::string& kodeNegara,
                     AnggotaNegara& hasil) const;
    bool tampilkanAnggota(const std::string& kodeOrganisasi, std::ostream& out) const;
    void tampilkanSemua(std::ostream& out) const;

private:
    mll::ListOrganisasi organisasi;
};
