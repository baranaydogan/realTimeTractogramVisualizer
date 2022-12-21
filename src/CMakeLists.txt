PROJECT(RealTimeTractogramVisualizer)

cmake_minimum_required(VERSION 3.20.0)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-multiple-definition")

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
   message (STATUS "This software requires VTK9 or newer")
   return()
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

if (NOT Qt6_FOUND)
   message("QT6 not found")
   return()
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
	${TREKKER_LIB}/libTrekker.a
    	Qt${QT_VERSION_MAJOR}::Core
    	Qt${QT_VERSION_MAJOR}::Gui
    	Qt${QT_VERSION_MAJOR}::Widgets
	${VTK_LIBRARIES}
	${ACVD_LIBRARIES}
	/usr/lib/libz.a
	)

INSTALL(TARGETS rttvis DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../bin)




