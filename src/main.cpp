#include "aplikasi.hpp"

#include <iostream>
#include <string_view>

int main(int argc, char* argv[]) {
    if (argc > 2 || (argc == 2 && std::string_view{argv[1]} != "--demo")) {
        std::cerr << "Penggunaan: kenegaraan [--demo]\n";
        return 1;
    }

    Aplikasi aplikasi;
    aplikasi.jalankan(std::cin, std::cout, argc == 2);
}
