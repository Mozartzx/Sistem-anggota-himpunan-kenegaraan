# Sistem Anggota Himpunan Kenegaraan

Tugas besar Struktur Data S1 Rekayasa Perangkat Lunak. Program terminal C++ ini mencatat organisasi antarnegara dan negara anggotanya dengan **Multi Linked List**. Setiap node organisasi mempunyai linked list anggota sendiri.

| Keterangan | Data |
| --- | --- |
| Kelompok | Gw EsEr |
| Ketua | Fanan Agfian Mozart |
| Anggota | Raihan Yassar Tsaqib |

[Laporan tugas besar](LAPORAN.md) berisi tujuan, studi kasus, diagram class dan ADT, rujukan kode, hasil pengujian, analisis, serta kesimpulan.

## Menjalankan program di Windows

Gunakan compiler C++17, CMake, dan MinGW Make. Jika menggunakan MinGW bawaan Code::Blocks di lokasi berikut, jalankan baris pertama untuk menambahkan compiler, CMake, dan runtime MinGW ke PATH sesi PowerShell. Sesuaikan lokasi bila instalasi berbeda.

```powershell
$env:Path = 'C:\Program Files\CodeBlocks\MinGW\bin;' + $env:Path
cmake -S . -B build -G 'MinGW Makefiles'
cmake --build build
.\build\kenegaraan.exe --demo
```

Pilih **9** untuk melihat ketiga organisasi dan kelima contoh anggota di tiap organisasi. Jalankan `.\build\kenegaraan.exe` tanpa argumen untuk mulai dengan daftar kosong. Kode organisasi dan negara peka huruf besar/kecil. Pakai `ASEAN`, `PBB`, atau `OPEC` untuk mencari organisasi demo. Perubahan data berlaku selama program berjalan.

| Menu | Operasi |
| --- | --- |
| 1–4 | Tambah, hapus, cari, dan tampilkan organisasi |
| 5–8 | Tambah, hapus, cari, dan tampilkan anggota pada organisasi tertentu |
| 9 | Tampilkan semua organisasi beserta anggotanya |
| 0 | Keluar |

## Menjalankan pengujian

Setelah membangun program, jalankan perintah berikut di sesi PowerShell yang sama.

```powershell
ctest --test-dir build --output-on-failure
.\build\uji_mll.exe
```
