Instalasi PlatformIO di Windows
===============================

## Requirements

Berikut adalah software-software yang diperlukan untuk menginstal PlatformIO di Windows.

* Python 2.7

#### Instalasi Python 2.7

PlatformIO hanya bisa digunakan jika versi Python yang diinstall adalah versi 2.7.

Untuk menginstal Python 2.7, unduh installer di python.org lalu jalankan software installer. Jika halaman atau dialog "Customize Python 2.7.14" muncul, pilih opsi "Will be installed on local hard drive" pada menu "Add python.exe to path". Lalu ikuti proses instalasi sampai selesai.

#### Cek Instalasi Python 2.7

Buka command propmt, lalu ketik perintah berikut:

```sh
python --version
```

Periksa output dari perintah tersebut. Jika terdapat teks sperti berikut, maka kemungkinan besar Python sudah terinstal pada Windows namun tidak dikenali oleh command prompt.

```
'python' is not recognized as an internal or external command, operable program or batch file.
```

Agar dikenali oleh command prompt, lakukan langkah-langkah berikut:

* Buka file explorer.
* Klik kanan pada "This PC" atau "My Computer".
* Klik pada menu "Properties".
* Klik pada menu "Advanched system settings".
* Klik pada tombol "Environment Variables".
* Pilih variabel "Path" pada bagian "System variables", lalu klik tombol edit.
* Pada Windows 10, klik tombol "New" lalu tambahkan "C:\Python27" dan "C:\Python27\Scripts".
* Pada Windows 7, 8, dan 8.1, tambahkan ";C:\Python27;C:\Python27\Scripts;" pada isian "Variable value".
* Lalu klik OK sampai anda keluar dari pengaturan environment variables.
* Restart command prompt.

Lalu cek kembali instalasi python dengan cara yang sama seperti sebelumnya.

```
python --version
```

Jika output dari perintah di atas mirip atau sama dengan teks berikut, maka interperter Python sudah dikenali oleh command prompt.

```
Python 2.7.14
```

#### Cek Instalasi PIP (Package Manager untuk Python)

PIP merupakan package manager untuk bahasa pemrograman Python. Biasanya, PIP sudah terinstall bersamaan dengan interpreter Python. Kita dapat menggunakan cara yang sama  dengan cara mengecek intstalasi interpreter Python untuk mengecek apakah PIP sudah dikenali oleh command prompt atau belum.

```
pip --version
```

Periksa output dari perintah tersebut, jika muncul teks seperti berikut, maka periksa kembali environment variable "Path" dengan cara yang sama ketika "memperkenalkan" Python interpreter kepada command prompt.

```
'pip' is not recognized as an internal or external command, operable program or batch file.
```

Jika muncul teks seperti berikut, maka PIP sudah dikenali oleh command prompt.

```
pip 9.0.1 from c:\python27\lib\site-packages (python 2.7)
```

#### Instal PlatformIO

Untuk menginstal PlatformIO, buka command prompt dan ketik perintah berikut lalu ketik enter.

```
pip install platformio
```

Tunggu beberapa saat, jika koneksi internet lancar maka proses instalasi akan berjalan dengan lancar juga.

#### Cek Instalasi PlatformIO

Cek instalasi PlatformIO dengan menggunakan cara yang sama dengan cara sebelumnya.

```
platformio --version
```

Jika muncul teks seperti berikut, maka proses instalasi PlatformIO sudah selesai.

```
PlatformIO, version 3.4.1
```

Namun jika yang muncul adalah teks seperti berikut, maka proses instalasi PlatformIO dikatakan gagal.

```
'platformio' is not recognized as an internal or external command, operable program or batch file.
```

