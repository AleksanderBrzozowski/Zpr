Projekt na przedmiot ZPR

Przedmiotem projektu jest symulator systemu kamer w ruchu drogowym.

Autorzy: Aleksander Brzozowski, Piotr Kuc, Paweł Rybak


1. WYMAGANIA
=============

Do skompilowania projektu niezbędne są:

- Biblioteki Qt5 
- CMake w wersji co najmniej 3.6
- W przypadku systemu Linux niezbędny jest program make
- Kompilator C++ (VS, g++, etc.)

2. PRZYGOTOWANIE
================

a. Instalacja biblioteki Qt5:
------------------------------

- W systemach korzystających z repozytoriów Debiana (m.in. Ubuntu)
wystarczy zainstalować paczkę "qt5base-dev".
- W przypadku pozostałych systemów należy zainstalować Qt pobierając
go wpierw ze strony projektu - https://www.qt.io/download-open-source/
- W przypadku gdy CMake nie znajdzie automatycznie ścieżki do bibliotek
Qt, należy w pliku src/GUI/CMakeLists.txt odkomentować linijkę:
"set (CMAKE_PREFIX_PATH "C:\\Qt\\5.7\\msvc2015_64")", oraz wstawić
odpowiednią ścieżkę do biblioteki.

b. Instalacja CMake:
--------------------

- Należy pobrać CMake ze strony projektu https://cmake.org/download/
oraz zainstalować go zgodnie z załączoną doń instrukcją.

3. INSTALACJA
=============

Instalacja polega na wywołaniu programu CMake podając jako
argument ścieżkę do folderu w którym znajduje się projekt.

W przypadku systemu z rodziny Linux lub Windows korzystając ze środowiska 
MinGW, polecenie to wygeneruje plik Makefile. Wywołanie komendy 'make' 
skompiluje projekt i wygeneruje plik wykonywalny 'Zpr_run'.

W przypadku systemu Windows, korzystającego z kompilatora Visual Studio
wygenerowany zostanie projekt Visual Studio, który należy skompilować
odpowiednim kompilatorem.

4. INSTALACJA KROK PO KROKU
===========================

*************************************************
* Zakłada się spełnienie warunków z punktu 1.   *
* oraz że znajdujemy się w katalogu z projektem *
*************************************************

Systemy z rodziny Linux
-----------------------

W terminalu:
mkdir build && cd build  # stworzenie i przejście do katalogu build
cmake ../  # uruchomienie CMake
make  # kompilacja i konsolidacja projektu
./Zpr_run  # uruchomienie programu

Systemy Windows
---------------------------------------
UWAGA!
W miejsce $GENERATOR należy wstawić jakim kompilatorem będzie kompilowany
projekt. Może to być istotne, gdyż domyślna architektura (x86) może być
niezgodna z architekturą biblioteki Qt. Przykładową wartością w to miejsce
może być "Visual Studio 14 2015 Win64".

W środowisku Power Shell:
mkdir build # stworzenie katalogu build
cd build # przejście do katalogu build
cmake -G "$GENERATOR" ../ # uruchomienie CMake
cmake --build . # wywołanie kompilatora za pośrednictwem CMake

