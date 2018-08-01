rm -rf my_build
mkdir my_build
cd my_build
cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/local/bin/g++-8 .. && make -j4 && ctest -VV
