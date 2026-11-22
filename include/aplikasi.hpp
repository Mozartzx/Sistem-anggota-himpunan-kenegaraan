#pragma once

#include "sistem_keanggotaan.hpp"

class Aplikasi {
public:
    void jalankan(std::istream& in, std::ostream& out, bool demo);

private:
    void tampilkanMenu(std::ostream& out) const;
    bool prosesPilihan(int pilihan, std::istream& in, std::ostream& out);
    void isiDataContoh();

    SistemKeanggotaan sistem;
};
