//
// Created by Roman on 17-Jun-22.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include <stdio.h>

struct decoder {
    struct node *tree_root;
    FILE *src_file;
    FILE *output_file;
};

struct decoder decoder_create(struct node *tree_root, FILE *src_file, FILE *output_file);
void decoder_destroy(struct decoder *decoder);
void decoder_decode(struct decoder *decoder);

#endif //HUFFMAN_DECODER_H
