//
// Created by Roman on 10-Jun-22.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <stdio.h>

#define WRITE_BUFFER_SIZE 4096

struct encoder {
    struct codebook *codebook;
    FILE *src_file;
    FILE *output_file;
};

struct encoder encoder_create(struct codebook *codebook, FILE *src_file, FILE *output_file_name);
void encoder_destroy(struct encoder *encoder);
void encoder_encode(struct encoder *encoder);

#endif //HUFFMAN_ENCODER_H
