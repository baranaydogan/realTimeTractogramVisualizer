#!/bin/bash

# SET PATHS AND CONFIGURATION

# Path to the cmake executable
cmakeExe=/home/baran/dev/cmake/bin/cmake

# Path to the compilers
c_compiler=gcc-8
cxx_compiler=g++-8

# VTK cmake dir
VTK_DIR=/opt/VTK/VTK-9.1.0-static/lib/cmake/vtk-9.1

# ACVD cmake dir
ACVD_DIR=/opt/ACVD/ACVD-static/lib/cmake/ACVD

# Path to Trekker (below is an example)
trekkerSrc=/home/baran/dev/trekker/src
trekkerLib=/home/baran/dev/trekker/build/Linux/install/lib

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
-DQT_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6 \
-DQt6_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6 \
-DQt6Core_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6Core \
-DQt6CoreTools_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6CoreTools \
-DQt6DBus_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6DBus \
-DQt6DBusTools_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6DBusTools \
-DQt6Gui_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6Gui \
-DQt6GuiTools_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6GuiTools \
-DQt6OpenGL_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6OpenGL \
-DQt6OpenGLWidgets_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6OpenGLWidgets \
-DQt6Widgets_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6Widgets \
-DQt6WidgetsTools_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6WidgetsTools \
-DQt6BundledPcre2_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6BundledPcre2 \
-DQt6BundledLibpng_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6BundledLibpng \
-DQt6BundledHarfbuzz_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6BundledHarfbuzz \
-DQt6BundledFreetype_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6BundledFreetype \
-DCMAKE_C_COMPILER=${c_compiler} \
-DCMAKE_CXX_COMPILER=${cxx_compiler} \
-DVTK_DIR=${VTK_DIR} \
-DACVD_DIR=${ACVD_DIR} \
-DTREKKER_SRC=${trekkerSrc} \
-DTREKKER_LIB=${trekkerLib} \
-DCMAKE_BUILD_TYPE=${buildType} ..

${cmakeExe} \
--build . \
--config ${buildType} \
--target install \
--parallel 16

cd ..
