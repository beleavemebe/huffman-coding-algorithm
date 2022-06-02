cmake_minimum_required(VERSION 3.17)
project(huffman C)

set(CMAKE_C_STANDARD 99)

add_executable(huffman include/node.h src/node.c include/heap.h test/test.h src/heap.c test/heap_test.c)