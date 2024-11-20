mkdir -p build
cd build
cmake ..
make
cd ..
c++ -o results/bin/executable src/main.cpp -Iinclude -Lbuild -lipb_arithmetic