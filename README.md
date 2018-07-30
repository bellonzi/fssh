[![Build Status](https://travis-ci.org/bellonzi/fssh.svg?branch=master)](https://travis-ci.org/bellonzi/fssh)

How to build:
=============

 - git clone https://github.com/bellonzi/fssh.git
 - cd fssh
 - mkdir build
 - cd build
 - cmake ..
 - make
 - ctest -VV

To override your default C and C++ compilers, you can use the following instead (for example):
```
cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/local/bin/g++-8 ..
```

# Dependencies

These implementations depend on the nlohmann/json and armadillo libraries. On MacOS, you can get armadillo with
```
brew install armadillo
```
JSON is supplied through cmake.
