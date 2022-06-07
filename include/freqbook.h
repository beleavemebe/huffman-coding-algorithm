//
// Created by Roman on 06-Jun-22.
//

#ifndef HUFFMAN_FREQBOOK_H
#define HUFFMAN_FREQBOOK_H

#define FREQBOOK_SIZE 256

struct freqbook {
    int *frequencies;
};

struct freqbook freqbook_create();
void freqbook_destroy(struct freqbook *freqbook);
int freqbook_get_freq(struct freqbook *freqbook, char c);
void freqbook_inc_freq(struct freqbook *freqbook, char c);
struct heap freqbook_to_node_heap(struct freqbook *freqbook);
void freqbook_digest_string(struct freqbook *freqbook, char* string);

#endif //HUFFMAN_FREQBOOK_H
