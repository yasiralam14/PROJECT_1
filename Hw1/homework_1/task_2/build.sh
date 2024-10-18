mkdir -p build
c++ -c -I include src/subtract.cpp -o build/subtract.o
c++ -c -I include src/sum.cpp -o build/sum.o
ar rcs build/libipb_arithmetic.a build/subtract.o build/sum.o
c++ -o results/bin/executable src/main.cpp -Iinclude -Lbuild -lipb_arithmetic





