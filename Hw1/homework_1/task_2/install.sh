mkdir -p "./install/include"

cp "./include/"*.hpp "./install/include/"

cp "./results/lib/libipb_arithmetic.a" "./install"

cd install

cmake ..

make install