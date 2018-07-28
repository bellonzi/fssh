How to build:
=============

 - git clone https://github.com/bellonzi/FSSH_C.git
 - cd FSSH_C
 - mkdir build
 - cd build
 - cmake ..
 - cmake --build .
 - ctest -VV

To override your default C and C++ compilers, you can use the following instead (for example):
```
cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/local/bin/g++-8 ..
```

# Dependencies

These implementations depend on the FFTW3 and armadillo libraries. On MacOS, you can get these with
```
brew install armadillo fftw
```
