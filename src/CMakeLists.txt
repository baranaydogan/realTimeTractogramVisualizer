PROJECT(RealTimeTractogramVisualizer)

cmake_minimum_required(VERSION 3.15.0)

list(INSERT CMAKE_MODULE_PATH 0 "/usr/lib/cmake/OpenVDB")

SET(COMPILER_FLAG_TO_ENABLE_MULTITHREADING    "-D ENABLE_MULTITHREADING")
SET(CMAKE_CXX_FLAGS  "-Wno-deprecated ${CMAKE_CXX_FLAGS} ${COMPILER_FLAG_TO_ENABLE_MULTITHREADING}")
SET(CMAKE_EXE_LINKER_FLAGS  "-Wno-deprecated ${CMAKE_EXE_LINKER_FLAGS} ${COMPILER_FLAG_TO_ENABLE_MULTITHREADING}")

set(ZNZLIB_PATH ${TREKKER_SRC}/nifticlib-2.0.0/znzlib/)
include_directories( ${ZNZLIB_PATH} )

include_directories(${TREKKER_SRC})
link_directories(${TREKKER_LIB})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

FIND_PACKAGE(VTK REQUIRED)
if (NOT VTK_FOUND)
  message("${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")

FIND_PACKAGE(ACVD REQUIRED)
if (ACVD_FOUND)
  message("ACVD found")
else ()
  message("ACVD not found")
  return ()
endif()

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
if (NOT QT6_FOUND)
  message("QT6 found")
else ()
  message("QT6 not found")
  return ()
endif()

SET(rttvis_app_SRCS 
	main.cpp
	rttvis_app.cpp
	trekker_interface.cpp
	brainmesh_handler.cpp
	aux.cpp
	)

SET(rttvis_app_MOC_HDRS 
	rttvis_app.h	
	)

SET(rttvis_app_UI 
	rttvis_app.ui
	)

QT6_WRAP_CPP(rttvis_app_MOC_SRCS ${rttvis_app_MOC_HDRS})
QT6_WRAP_UI(rttvis_app_UI_HDRS ${rttvis_app_UI})

ADD_EXECUTABLE(rttvis
	${rttvis_app_SRCS}
	${rttvis_app_MOC_SRCS}
	${rttvis_app_UI_HDRS})

target_link_libraries(rttvis
    pthread
	z
	Trekker
    Qt::Core
    Qt::Gui
    Qt::Widgets
	${VTK_LIBRARIES}
	${ACVD_LIBRARIES}
	)

INSTALL(TARGETS rttvis DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin/)




