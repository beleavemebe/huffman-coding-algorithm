//
// Created by Roman on 17-Jun-22.
//

#include <stdbool.h>
#include <malloc.h>
#include "../include/decoder.h"
#include "../include/buffers.h"
#include "../include/node.h"
#include "../include/codebook.h"
#include "../include/freqbook.h"
#include "../include/heap.h"

struct decoder decoder_create(FILE *src_file, FILE *output_file) {
    return (struct decoder) {
        .src_file = src_file,
        .output_file = output_file,
    };
}

void decoder_destroy(struct decoder *decoder) {
    decoder->src_file = NULL;
    decoder->output_file = NULL;
}

void decoder_decode(struct decoder *decoder) {
    int codes_to_read = 0;
    fread(&codes_to_read, sizeof(int), 1, decoder->src_file);

    int freqbook_size;
    fread(&freqbook_size, sizeof(int), 1, decoder->src_file);
    struct freqbook freqbook = freqbook_create();
    for (int i = 0; i < freqbook_size; ++i) {
        char c;
        int freq;

        fread(&c, sizeof(char), 1, decoder->src_file);
        fread(&freq, sizeof(int), 1, decoder->src_file);

        freqbook_set_freq(&freqbook, c, freq);
    }

    struct heap heap = freqbook_to_node_heap(&freqbook);
    while (heap.size > 1) {
        struct node *first_sibling = heap_pop(&heap);
        struct node *second_sibling = heap_pop(&heap);
        int combined_freq = first_sibling->freq + second_sibling->freq;
        struct node *father = node_create(combined_freq, 0, first_sibling, second_sibling);
        heap_push(&heap, father);
    }

    struct node *root = heap_pop(&heap);

    char *buf = calloc(READ_BUFFER_SIZE, sizeof(char));
    struct node *node = root;

    while (true) {
        int chars_read = (int) fread(buf, sizeof(char), READ_BUFFER_SIZE, decoder->src_file);
        if (chars_read == 0) {
            break;
        }

        char *output_buffer = calloc(chars_read * 8 + 1, sizeof(char));
        int bytes_written = 0;

        for (int i = 0; i < chars_read * 8; ++i) {
            char src = buf[i / 8];
            unsigned char bit = (((unsigned char) src) >> (8 - (i % 8) - 1)) & 1;
            switch (bit) {
                case 0:
                    node = node->right;
                    break;
                case 1:
                    node = node->left;
                    break;
                default:
                    break;
            }

            if (node->left == NULL && node->right == NULL) {
                sprintf(output_buffer + bytes_written++, "%c", node->value);
                node = root;
                codes_to_read--;
                if (codes_to_read == 0) break; // what the fuck
            }
        }

        fwrite(output_buffer, sizeof(char), bytes_written, decoder->output_file);
        free(output_buffer);
    }

    heap_destroy(&heap);
    freqbook_destroy(&freqbook);
}
