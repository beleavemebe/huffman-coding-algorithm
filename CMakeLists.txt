cmake_minimum_required(VERSION 3.17)
project(huffman C)

set(CMAKE_C_STANDARD 99)

add_executable(huffman src/main.c include/node.h src/node.c include/heap.h test/test.h src/heap.c test/heap_test.c include/freqbook.h test/node_test.c src/freqbook.c test/freqbook_test.c include/codebook.h src/codebook.c test/codebook_test.c)