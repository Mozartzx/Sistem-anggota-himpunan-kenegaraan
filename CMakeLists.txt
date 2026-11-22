cmake_minimum_required(VERSION 3.16)
project(SistemAnggotaHimpunanKenegaraan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(keanggotaan
    src/mll.cpp
    src/sistem_keanggotaan.cpp
)
target_include_directories(keanggotaan PUBLIC include)

add_executable(kenegaraan src/main.cpp src/aplikasi.cpp)
target_link_libraries(kenegaraan PRIVATE keanggotaan)

include(CTest)
if(BUILD_TESTING)
    add_executable(uji_mll tests/uji_mll.cpp)
    target_link_libraries(uji_mll PRIVATE keanggotaan)
    add_test(NAME operasi_mll COMMAND uji_mll)
endif()
