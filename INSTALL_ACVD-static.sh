#!/bin/bash

c_compiler=gcc-8
cxx_compiler=g++-8

cmake=/home/baran/dev/cmake/bin/cmake

rm -rf ./ACVD-static-build

mkdir ACVD-static-build

cd ACVD-static-build

${cmake} \
-G Ninja \
-DCMAKE_C_COMPILER=${c_compiler} \
-DCMAKE_CXX_COMPILER=${cxx_compiler} \
-DCMAKE_INSTALL_PREFIX=/opt/ACVD/ACVD-static \
-DCMAKE_EXE_LINKER_FLAGS="-Wl,--allow-multiple-definition" \
-DCMAKE_BUILD_TYPE=Release \
-DVTK_DIR=/opt/VTK/VTK-9.1.0-static/lib/cmake/vtk-9.1 \
-DBUILD_SHARED_LIBS=NO \
-DUSE_MULTITHREADING=YES \
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
-DQt6BundledFreetype_DIR=/opt/QT/QT-6.2.0-static/lib/cmake/Qt6BundledFreetype ..

cmake --build . --parallel
sudo cmake --install .

cd ..
