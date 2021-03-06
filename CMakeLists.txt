cmake_minimum_required (VERSION 2.8)
project (RooSignal)

set (RooSignal_VERSION_MAJOR 0)
set (RooSignal_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -m64 -Wno-overloaded-virtual -Wno-shadow -fPIC -fsigned-char")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined -rdynamic")
include_directories(${PROJECT_SOURCE_DIR}/include)

#ROOT stuff
find_program(ROOTEXE NAMES root PATHS $ENV{ROOTSYS}/bin )
find_program(ROOTCLING NAMES rootcling PATHS $ENV{ROOTSYS}/bin )
find_program(ROOTCONFIG NAMES root-config PATHS $ENV{ROOTSYS}/bin )

execute_process(COMMAND ${ROOTCONFIG} --libs OUTPUT_VARIABLE ROOTLIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${ROOTCONFIG} --glibs OUTPUT_VARIABLE ROOTGLIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${ROOTCONFIG} --cflags OUTPUT_VARIABLE ROOTCFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${ROOTCONFIG} --cflags OUTPUT_VARIABLE ROOTLDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

message(${ROOTCFLAGS})
message("Testing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOTCFLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${ROOTLDFLAGS} ${ROOTLIBS}")

#ROOT now set up


file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cxx)
message("SOURCES: ${SOURCES}")

message(${CMAKE_CURRENT_BINARY_DIR})

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")

add_library(RooSignal SHARED ${SOURCES})
