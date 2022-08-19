#!/bin/bash

c_compiler=gcc-8
cxx_compiler=g++-8

cmake=/home/baran/dev/cmake/bin/cmake

rm -rf ./QT-6.2.0-static-build

mkdir -p QT-6.2.0-static-build

cd QT-6.2.0-static-build

${cmake} \
-G Ninja \
-DCMAKE_C_COMPILER=${c_compiler} \
-DCMAKE_CXX_COMPILER=${cxx_compiler} \
-DCMAKE_INSTALL_PREFIX=/opt/QT/QT-6.2.0-static \
-DBUILD_SHARED_LIBS=OFF \
-DBUILD_WITH_PCH=OFF \
-DBUILD_qt3d=OFF \
-DBUILD_qt5compat=OFF \
-DBUILD_qtactiveqt=OFF \
-DBUILD_qtbase=ON \
-DBUILD_qtcharts=OFF \
-DBUILD_qtcoap=OFF \
-DBUILD_qtconnectivity=OFF \
-DBUILD_qtdatavis3d=OFF \
-DBUILD_qtdeclarative=OFF \
-DBUILD_qtdoc=OFF \
-DBUILD_qtimageformats=OFF \
-DBUILD_qtlottie=OFF \
-DBUILD_qtmqtt=OFF \
-DBUILD_qtmultimedia=OFF \
-DBUILD_qtnetworkauth=OFF \
-DBUILD_qtopcua=OFF \
-DBUILD_qtquick3d=OFF \
-DBUILD_qtquicktimeline=OFF \
-DBUILD_qtremoteobjects=OFF \
-DBUILD_qtscxml=OFF \
-DBUILD_qtsensors=OFF \
-DBUILD_qtserialbus=OFF \
-DBUILD_qtserialport=OFF \
-DBUILD_qtshadertools=OFF \
-DBUILD_qtsvg=OFF \
-DBUILD_qttools=OFF \
-DBUILD_qttranslations=OFF \
-DBUILD_qtvirtualkeyboard=OFF \
-DBUILD_qtwayland=OFF \
-DBUILD_qtwebchannel=OFF \
-DBUILD_qtwebengine=OFF \
-DBUILD_qtwebsockets=OFF \
-DBUILD_qtwebview=OFF \
-DFEATURE_xcb=ON \
-DFEATURE_concurrent=OFF \
-DFEATURE_dbus_linked=OFF \
-DFEATURE_network=OFF \
-DFEATURE_printsupport=OFF \
-DFEATURE_sql=OFF \
-DFEATURE_system_doubleconversion=OFF \
-DFEATURE_system_freetype=OFF \
-DFEATURE_system_harfbuzz=OFF \
-DFEATURE_system_jpeg=OFF \
-DFEATURE_system_libb2=OFF \
-DFEATURE_system_pcre2=OFF \
-DFEATURE_system_png=OFF \
-DFEATURE_system_zlib=OFF \
-DFEATURE_systemsemaphore=OFF \
-DFEATURE_systemtrayicon=OFF \
-DFEATURE_relocatable=ON \
-DFEATURE_testlib=OFF \
-DFEATURE_vulkan=OFF \
-DFEATURE_textodfwriter=OFF \
-DFEATURE_textmarkdownreader=OFF \
-DFEATURE_textmarkdownwriter=OFF \
-DFEATURE_style_stylesheet=ON \
-DFEATURE_icu=OFF \
-DFEATURE_forkfd_pidfd=OFF \
-DFEATURE_accessibility=OFF \
-DFEATURE_accessibility_atspi_bridge=OFF \
-DFEATURE_sessionmanager=OFF \
-DFEATURE_linuxfb=OFF \
-DFEATURE_eglfs_x11=OFF \
-DFEATURE_vkgen=OFF \
-DQT_BUILD_EXAMPLES_BY_DEFAULT=OFF \
-DQT_BUILD_TESTS_BY_DEFAULT=OFF ..

cmake --build . --parallel
sudo cmake --install .

cd ..

