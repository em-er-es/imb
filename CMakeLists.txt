# Image Processing Blocks
cmake_minimum_required(VERSION 2.8.3)
PROJECT(imb) # BASE

# Information
if(VERBOSE)
	message("C++ compiler supported C++ features:")
	foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
		message("-*- ${i}")
	endforeach()
endif()

# @reference https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake#31010221
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	add_compile_options(-std=c++11)
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	message(STATUS "Using C++11 standard")
elseif(COMPILER_SUPPORTS_CXX0X)
	add_compile_options(-std=c++0x)
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	message(STATUS "Using C++0x standard")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Profile
if(PROFILE)
	message(STATUS "Configuring for profiling build")
	add_compile_options(-pg)
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
	#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
	#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
	if(NOT DEBUG)
		set(DEBUG 1)
	endif()
endif()

# Debug
if(DEBUG)
	message(STATUS "Configuring for debug build")
	add_compile_options(-DDEBUG=${DEBUG})
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG=${DEBUG}")
	#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG=${DEBUG}")
endif()

# Dependencies
find_package(OpenCV REQUIRED)

# Configuration
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(OUTPUT imb)
set(SOURCE_CODE
	source/imb.cpp
	source/arguments.cpp
	source/common.cpp
	source/display.cpp
	source/file.cpp
	source/processor.cpp
	source/filter_c64.cpp
)

message("OpenCV configuration: ")
message("-*- version: " ${OpenCV_VERSION})
if(VERBOSE)
	message("-*- compute capabilities: " ${OpenCV_COMPUTE_CAPABILITIES})
	message("-*- location: " ${OpenCV_INSTALL_PATH})
	message("-*- include directories: " ${OpenCV_INCLUDE_DIRS})
	message("-*- cmake configuration directory: " ${OpenCV_DIR})
	message("-*- libraries directory: " ${OpenCV_LIB_DIR})
	message("-*- libraries: " ${OpenCV_LIBS})
endif()

# IMB
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${OpenCV_INCLUDE_DIRS}
)

link_directories(${CMAKE_BINARY_DIR}/bin ${OpenCV_LIB_DIR})
add_executable(${OUTPUT} ${SOURCE_CODE})
target_link_libraries(${OUTPUT} ${OpenCV_LIBS})
