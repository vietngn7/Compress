cmake_minimum_required(VERSION 3.6)
project(untitled_folder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Compressor.cpp
    Compressor.hpp
    Counting.cpp
    Counting.hpp
    Decompressor.cpp
    Decompressor.hpp
    Huffman.cpp
    Huffman.hpp
    main.cpp
    Node.cpp
    Node.hpp
        ShannonF.cpp ShannonF.h)

add_executable(untitled_folder ${SOURCE_FILES})