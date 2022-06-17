//
// Created by Roman on 17-Jun-22.
//

#include <stdbool.h>
#include <malloc.h>
#include "../include/decoder.h"
#include "../include/buffers.h"
#include "../include/node.h"

struct decoder decoder_create(struct node *tree_root, FILE *src_file, FILE *output_file) {
    return (struct decoder) {
        .tree_root = tree_root,
        .src_file = src_file,
        .output_file = output_file,
    };
}

void decoder_destroy(struct decoder *decoder) {
    decoder->tree_root = NULL;
    decoder->src_file = NULL;
    decoder->output_file = NULL;
}

void decoder_decode(struct decoder *decoder) {
    char *buf = calloc(READ_BUFFER_SIZE, sizeof(char));
    struct node *node = decoder->tree_root;

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
                node = decoder->tree_root;
            }
        }

        fwrite(output_buffer, sizeof(char), bytes_written, decoder->output_file);
        free(output_buffer);
    }
}
