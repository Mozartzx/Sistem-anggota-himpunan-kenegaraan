#pragma once

#include "sistem_keanggotaan.hpp"

#include <iosfwd>

class Aplikasi {
public:
void jalankan(istream& in, bool demo);

private:
    void tampilkanMenu() const;
    bool prosesPilihan(int pilihan, istream& in);
    void isiDataContoh();

    SistemKeanggotaan sistem;
};
