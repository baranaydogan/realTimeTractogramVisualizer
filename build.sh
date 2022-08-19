#!/bin/bash

# SET PATHS AND CONFIGURATION

# Path to the cmake executable
cmakeExe=cmake

# Path to the compilers
c_compiler=gcc
cxx_compiler=g++

# VTK cmake dir
VTK_DIR=/opt/VTK-9.1.0-static/lib/cmake/vtk-9.1

# ACVD cmake dir
ACVD_DIR=/opt/ACVD-static/lib/cmake/ACVD

# Path to Trekker (below is an example)
trekkerSrc=/home/baran/Work/code/trekker/src
trekkerLib=/home/baran/Work/code/trekker/build/Linux/install/lib

# Release or Debug
buildType=Release


# MAKE A CLEAN INSTALL

# Delete the existing build directory
rm -rf build

# Make a build directory
mkdir -p build

: '
-DEGL_LIBRARY=/usr/lib/libEGL_nvidia.so \
-DOPENGL_egl_LIBRARY=/usr/lib/libEGL_nvidia.so \
-DOPENGL_gles2_LIBRARY=/usr/lib/libGLESv2_nvidia.so \
-DOPENGL_gles3_LIBRARY=/usr/lib/libGLESv2_nvidia.so \
-DOPENGL_glx_LIBRARY=/usr/lib/libGLX_nvidia.so \
-Dharfbuzz_DIR=/opt/harfbuzz-5.1.0-static \
-DPNG_LIBRARY_RELEASE=/opt/libpng-1.6.37-static/lib/libpng16.a \
-DPNG_PNG_INCLUDE_DIR=/opt/libpng-1.6.37-static/include/ \
'

: '
-DQt6_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6 \
-DQt6Core_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6Core \
-DQt6Widgets_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6Widgets \
-DQt6Gui_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6Gui \
-DQt6BundledPcre2_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6BundledPcre2 \
-DQt6BundledLibpng_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6BundledLibpng \
-DQt6BundledHarfbuzz_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6BundledHarfbuzz \
-DQt6BundledFreetype_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6BundledFreetype \
-DQt6BundledLibjpeg_DIR=/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6BundledLibjpeg \
-DQT_FEATURE_shared=OFF \
-DQT_FEATURE_rpath=OFF \
-DQT_FEATURE_journald=OFF \
-DQT_FEATURE_intelcet=OFF \
-DQT_FEATURE_system_xcb_xinput=OFF \
'

# Build
cd build
${cmakeExe} \
-DQt6_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6 \
-DQt6Core_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6Core \
-DQt6CoreTools_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6CoreTools \
-DQt6DBus_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6DBus \
-DQt6DBusTools_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6DBusTools \
-DQt6Gui_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6Gui \
-DQt6GuiTools_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6GuiTools \
-DQt6OpenGL_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6OpenGL \
-DQt6OpenGLWidgets_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6OpenGLWidgets \
-DQt6Widgets_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6Widgets \
-DQt6WidgetsTools_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6WidgetsTools \
-DQt6BundledPcre2_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6BundledPcre2 \
-DQt6BundledLibpng_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6BundledLibpng \
-DQt6BundledHarfbuzz_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6BundledHarfbuzz \
-DQt6BundledFreetype_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6BundledFreetype \
-DQt6BundledLibjpeg_DIR=/opt/QT/QT6.3.0/lib/cmake/Qt6BundledLibjpeg \
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
