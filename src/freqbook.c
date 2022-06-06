//
// Created by Roman on 06-Jun-22.
//
#include <stdlib.h>
#include "..\include\freqbook.h"
#include "..\include\node.h"
#include "..\include\heap.h"


struct freqbook freqbook_create() {
    return (struct freqbook) {
        .frequencies = calloc(256, sizeof(int))
    };
}

void freqbook_destroy(struct freqbook *freqbook) {
    free(freqbook->frequencies);
    freqbook->frequencies = (int *) NULL;
}

int freqbook_get_freq(struct freqbook *freqbook, char c) {
    return freqbook->frequencies[(unsigned char) c];
}

void freqbook_inc_freq(struct freqbook *freqbook, char c) {
    freqbook->frequencies[(unsigned char) c] += 1;
}

struct heap freqbook_to_node_heap(struct freqbook *freqbook) {
    struct heap heap = heap_create();

    for (int i = 0; i < FREQBOOK_SIZE; ++i) {
        if (freqbook->frequencies[i] != 0) {
            struct node *node = node_create(freqbook->frequencies[i], (char) i, NULL, NULL);
            heap_push(&heap, node);
        }
    }

    return heap;
}