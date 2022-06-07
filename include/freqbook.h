//
// Created by Roman on 06-Jun-22.
//

#ifndef HUFFMAN_FREQBOOK_H
#define HUFFMAN_FREQBOOK_H

#include <stdio.h>

#define FREQBOOK_SIZE 256

struct freqbook {
    int *frequencies;
};

struct freqbook freqbook_create();
void freqbook_destroy(struct freqbook *freqbook);
int freqbook_get_freq(struct freqbook *freqbook, char c);
void freqbook_inc_freq(struct freqbook *freqbook, char c);
struct heap freqbook_to_node_heap(struct freqbook *freqbook);
void freqbook_digest_string(struct freqbook *freqbook, char *string, int string_length);

#define BUFFER_SIZE 1024

struct freqbook_inflater {
    struct freqbook *freqbook;
    FILE *file;
};

struct freqbook_inflater freqbook_inflater_create(struct freqbook *freqbook, FILE *file);
void freqbook_inflater_destroy(struct freqbook_inflater *inflater);
void freqbook_inflater_inflate(struct freqbook_inflater *inflater);

#endif //HUFFMAN_FREQBOOK_H
