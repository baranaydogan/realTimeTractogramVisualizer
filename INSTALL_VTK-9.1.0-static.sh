#!/bin/bash

c_compiler=gcc-8
cxx_compiler=g++-8

cmake=/home/baran/dev/cmake/bin/cmake

rm -rf ./VTK-9.1.0-static-build

mkdir VTK-9.1.0-static-build

cd VTK-9.1.0-static-build

${cmake} \
-G Ninja \
-DCMAKE_C_COMPILER=${c_compiler} \
-DCMAKE_CXX_COMPILER=${cxx_compiler} \
-DCMAKE_INSTALL_PREFIX=/opt/VTK/VTK-9.1.0-static \
-DCMAKE_BUILD_TYPE=Release \
-DBUILD_SHARED_LIBS=NO \
-DHAVE_EGL=YES \
-DVTK_GROUP_ENABLE_StandAlone=YES \
-DVTK_GROUP_ENABLE_Qt=YES \
-DVTK_MODULE_ENABLE_VTK_GUISupportQtQuick=NO \
-DVTK_MODULE_ENABLE_VTK_GUISupportQtSQL=NO \
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
