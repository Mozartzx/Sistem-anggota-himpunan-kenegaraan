#include "aplikasi.hpp"

#include <iostream>
#include <string_view>

int main(int argc, char* argv[]) {
    if (argc > 2 || (argc == 2 && string_view{argv[1]} != "--demo")) {
        cout << "Penggunaan: kenegaraan [--demo]\n";
        return 1;
    }

    Aplikasi aplikasi;
    aplikasi.jalankan(cin, argc == 2);
}
