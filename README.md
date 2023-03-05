# Cultivation
This is an old game project I wrote during university for fun and practice. 


## Dependencies
These instructions are made for building on Windows 11. They likely work on other Windows versions as well.

Unpack the 64bit version (has to match your mingw installation) of the following dependencies into `C:\mingw_dev_lib`

* SFML 2 (https://www.sfml-dev.org/download/sfml/2.5.1/ - get the version that matches your compiler! For g++ you may need to build SFML yourself..?))

* Add `C:\mingw_dev_lib\bin` to your path! (otherwise the .exe won't run!)

Install `mingw` and `make`, run `make` in the base folder of this repository to build.
* `choco install mingw`
* `choco install make`
