rmdir /s /q build
cmake -B build -S . -G "MinGW Makefiles"
cmake --build build
