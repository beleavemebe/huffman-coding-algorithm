//
// Created by Roman on 10-Jun-22.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <stdio.h>

struct encoder {
    struct freqbook *freqbook;
    struct codebook *codebook;
    FILE *src_file;
    FILE *output_file;
};

struct encoder encoder_create(struct freqbook *freqbook, struct codebook *codebook, FILE *src_file, FILE *output_file_name);
void encoder_destroy(struct encoder *encoder);
void encoder_encode(struct encoder *encoder, char* output_filename);

#endif //HUFFMAN_ENCODER_H
