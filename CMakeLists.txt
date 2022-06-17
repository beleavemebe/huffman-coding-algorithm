cmake_minimum_required(VERSION 3.17)
project(huffman C)

set(CMAKE_C_STANDARD 99)

add_executable(huffman src/main.c include/node.h src/node.c include/heap.h #[[test/test.h test/heap_test.c test/node_test.c test/freqbook_test.c test/codebook_test.c]] src/heap.c include/freqbook.h src/freqbook.c include/codebook.h src/codebook.c include/encoder.h src/encoder.c include/decoder.h src/decoder.c include/buffers.h)