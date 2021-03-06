//
// Created by Roman on 06-Jun-22.
//

#include <stdlib.h>
#include "..\include\freqbook.h"
#include "..\include\node.h"
#include "..\include\heap.h"
#include "..\include\buffers.h"


struct freqbook freqbook_create() {
    return (struct freqbook) {
        .frequencies = calloc(256, sizeof(int))
    };
}

void freqbook_destroy(struct freqbook *freqbook) {
    free(freqbook->frequencies);
    freqbook->frequencies = NULL;
}

int freqbook_get_freq(struct freqbook *freqbook, char c) {
    return freqbook->frequencies[(unsigned char) c];
}

void freqbook_set_freq(struct freqbook *freqbook, char c, int freq) {
    freqbook->frequencies[(unsigned char) c] = freq;
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

void freqbook_digest_string(struct freqbook *freqbook, char *string, int string_length) {
    for (int i = 0; i < string_length; ++i) {
        freqbook_inc_freq(freqbook, string[i]);
    }
}

struct freqbook_inflater freqbook_inflater_create(struct freqbook *freqbook, FILE *file) {
    return (struct freqbook_inflater) {
        .freqbook = freqbook,
        .file = file,
    };
}

void freqbook_inflater_destroy(struct freqbook_inflater *inflater) {
    inflater->freqbook = NULL;
    inflater->file = NULL;
}

void freqbook_inflater_inflate(struct freqbook_inflater *inflater) {
    char *buf = calloc(READ_BUFFER_SIZE, sizeof(char));

    while (true) {
        int chars_read = (int) fread(buf, 1, READ_BUFFER_SIZE, inflater->file);
        if (chars_read == 0) break;
        freqbook_digest_string(inflater->freqbook, buf, chars_read);
    }

    free(buf);
}

int freqbook_get_amount_of_frequencies(struct freqbook *freqbook) {
    int result = 0;
    for (int i = 0; i < FREQBOOK_SIZE; ++i) {
        if (freqbook_get_freq(freqbook, (char) i) != 0) {
            result++;
        }
    }
    return result;
}
