# CommandLineInterface

This package contains three libraries:
- CommandLineInterface parses command line arguments,
- TextAttributes sets text attributes such as foreground color, background color, or style (bold, bright, underlined),
- Utilities provides helper functions:
  - *Show* allows thread safe output of arguments,
  - *FileExists*, and *DirectoryExists* check if a file or directory exists,
  - *IsDirectory* can be used to check if a provided path points to a directory,
  - *GetFilesInDirectory* provides a vector with the names of all files in a given directory,
  - *IsNan*, *IsInfinite*, and *IsPowerOfTwo* check simple properties of a number,
  - *CreateIndex*, *CreateReverseIndex*, and *UniqueIndex* create different indices of a provided array.

-----------------------------------------
 Installation
-----------------------------------------

This package can be installed with cmake:
```
mkdir build;
cd build;
cmake ../;
make install;
```
will compile the libraries in a new subdirectory called build (can be any name you choose), and installed in ~/lib. If the libraries are to be installed in a different path of form ```<PREFIX>/lib```, use
```
cmake ../ -DCMAKE_INSTALL_PREFIX=<PREFIX>;
```
instead.

If the installation directory does not exist it will be created.
