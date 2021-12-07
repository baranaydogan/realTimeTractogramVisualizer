#!/bin/bash



# SET PATHS AND CONFIGURATION

# Path to the cmake executable
cmakeExe=cmake

# Path to the compilers
c_compiler=gcc
cxx_compiler=g++

# Path to Trekker
trekkerSrc=/home/baran/Work/code/trekker/src
trekkerLib=/home/baran/Work/code/trekker/build/Linux/install/lib

# Release or Debug
buildType=Release





# MAKE A CLEAN INSTALL

# Delete the existing build directory
rm -rf build

# Make a build directory
mkdir -p build

# Build
cd build
${cmakeExe} \
-DCMAKE_C_COMPILER=${c_compiler} \
-DCMAKE_CXX_COMPILER=${cxx_compiler} \
-DTREKKER_SRC=${trekkerSrc} \
-DTREKKER_LIB=${trekkerLib} \
-DCMAKE_BUILD_TYPE=${buildType} ..

${cmakeExe} \
--build . \
--config ${buildType} \
--target install \
--parallel 16

cd ..
