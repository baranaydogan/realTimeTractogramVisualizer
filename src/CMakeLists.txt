PROJECT(RealTimeTractogramVisualizer)

cmake_minimum_required(VERSION 3.20.0)

set (CMAKE_CXX_STANDARD 17)


set(VTK_DIR "/opt/VTK-9.1.0-static/lib/cmake/vtk-9.1")
set(ACVD_DIR "/opt/ACVD-static/lib/cmake/ACVD")

# set(TREKKER_SRC "/home/baran/Work/code/trekker/src")
# set(TREKKER_LIB "/home/baran/Work/code/trekker/build/Linux/install/lib")

# set(QT_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6")
# set(Qt6_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6")
# set(Qt6Core_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6Core")
# set(Qt6Widgets_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6Widgets")
# set(Qt6Gui_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6Gui")
# set(Qt6CoreTools_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6CoreTools")
# set(Qt6DBusTools_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6DBusTools")
# set(Qt6GuiTools_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6GuiTools")
# set(Qt6OpenGL_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6OpenGL")
# set(Qt6OpenGLWidgets_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6OpenGLWidgets")
# set(Qt6WidgetsTools_DIR "/opt/QT/6.3.0-minimal-static/lib/cmake/Qt6WidgetsTools")
# set(QT_QMAKE_EXECUTABLE "/opt/QT/6.3.0-minimal-static/bin/qmake")

# -DEGL_LIBRARY=/usr/lib/libEGL_nvidia.so \
# -DOPENGL_egl_LIBRARY=/usr/lib/libEGL_nvidia.so \
# -DOPENGL_gles2_LIBRARY=/usr/lib/libGLESv2_nvidia.so \
# -DOPENGL_gles3_LIBRARY=/usr/lib/libGLESv2_nvidia.so \
# -DOPENGL_glx_LIBRARY=/usr/lib/libGLX_nvidia.so \

# set(GLESv2_LIBRARY /usr/lib/libGLESv2_nvidia.so)
# set(EGL_LIBRARY /usr/lib/libEGL_nvidia.so)
# set(OPENGL_egl_LIBRARY /usr/lib/libEGL_nvidia.so)

set(HAVE_EGL True)

set(CMAKE_BUILD_TYPE "Release")

list(INSERT CMAKE_MODULE_PATH 0 "/usr/lib/cmake/OpenVDB")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-multiple-definition")

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++ -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")

set(ZNZLIB_PATH ${TREKKER_SRC}/nifticlib-2.0.0/znzlib/)
include_directories( ${ZNZLIB_PATH} )

include_directories(${TREKKER_SRC})
link_directories(${TREKKER_LIB})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_definitions(-D ENABLE_MULTITHREADING)

FIND_PACKAGE(VTK REQUIRED)
if (NOT VTK_FOUND)
  message("${VTK_NOT_FOUND_MESSAGE}")
  message (STATUS "VTK not found")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")

if (${VTK_VERSION} LESS "9")
   if (${VTK_VERSION} LESS "8")
      if (${VTK_VERSION} LESS "7")
         message (STATUS "VTK version is too old. This software requires VTK7 or newer")
         return()
      else()
         SET(rttvis_gui_UI rttvis_gui_VTK7.ui)
         add_definitions(-D HAVE_VTK7)
         include(${VTK_USE_FILE})
         message (STATUS "Compiling with QVTKWidget")
      endif()
   else()
      SET(rttvis_gui_UI rttvis_gui_VTK8.ui)
      add_definitions(-D HAVE_VTK8)
      include(${VTK_USE_FILE})
      message (STATUS "Compiling with QVTKOpenGLWidget")
   endif()
else()
      SET(rttvis_gui_UI rttvis_gui_VTK9.ui)
      add_definitions(-D HAVE_VTK9)
      message (STATUS "Compiling with QVTKOpenGLStereoWidget")
endif()


FIND_PACKAGE(ACVD REQUIRED)
if (ACVD_FOUND)
  message(STATUS "ACVD found")
else ()
  message(STATUS "ACVD not found")
  return ()
endif()


# Add Tread
find_package (Threads)

SET(rttvis_gui_SRCS 
	main.cpp
	rttvis_gui.cpp
	trekker_interface.cpp
	brainmesh_handler.cpp
	aux.cpp
	)
	
SET(rttvis_gui_MOC_HDRS rttvis_gui.h)
SET(about_UI gui_about.ui)	

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets OpenGL)

if (NOT Qt6_FOUND)
   if (NOT Qt5_FOUND)
      message("QT5 or QT6 not found")
      return()
   else()
      message("QT5 found")
      QT5_ADD_RESOURCES(rttvis_gui_SRCS resources.qrc)
      QT5_WRAP_CPP(rttvis_gui_MOC_SRCS ${rttvis_gui_MOC_HDRS})
      QT5_WRAP_UI(rttvis_gui_UI_HDRS about_UI_HDRS ${rttvis_gui_UI})
   endif()
else()
   message("QT6 found")
   QT6_ADD_RESOURCES(rttvis_gui_SRCS resources.qrc)
   QT6_WRAP_CPP(rttvis_gui_MOC_SRCS ${rttvis_gui_MOC_HDRS})
   QT6_WRAP_UI(rttvis_gui_UI_HDRS about_UI_HDRS ${rttvis_gui_UI})
endif()


ADD_EXECUTABLE(rttvis
	${rttvis_gui_SRCS}
	${rttvis_gui_MOC_SRCS}
	${rttvis_gui_UI_HDRS})

target_link_libraries(rttvis
    	Threads::Threads
	z
	${TREKKER_LIB}/libTrekker.a
    	Qt${QT_VERSION_MAJOR}::Core
    	Qt${QT_VERSION_MAJOR}::Gui
    	Qt${QT_VERSION_MAJOR}::Widgets
	${VTK_LIBRARIES}
	${ACVD_LIBRARIES}
	)

INSTALL(TARGETS rttvis DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../bin)




