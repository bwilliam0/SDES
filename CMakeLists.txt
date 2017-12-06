cmake_minimum_required(VERSION 3.6)
project(SDES)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Key.cpp Key.h SDES.cpp SDES.h MasterHeader.h)
add_definitions(-DDEBUG_KEY)
#add_definitions(-DDEBUG_ECRYPTED_CIPHERTEXT)
add_executable(main ${SOURCE_FILES})