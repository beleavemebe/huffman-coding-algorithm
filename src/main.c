#include <stdio.h>
#include <string.h>
#include "../include/freqbook.h"
#include "../include/node.h"
#include "../include/heap.h"
#include "../include/codebook.h"
#include "../include/encoder.h"
#include "../include/decoder.h."

int encode(FILE *input_file, FILE *output_file, char *output_file_name);
int decode(FILE *input_file, FILE *output_file);

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage %s --[encode|decode] <input filename> <output filename>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[2], "rb");
    if (input_file == NULL) {
        printf("Could not open input file %s\n", argv[2]);
        return 2;
    }

    FILE *output_file = fopen(argv[3], "ab");
    if (output_file == NULL) {
        printf("Could not open input file %s\n", argv[3]);
        return 3;
    }

    char *option = argv[1];
    if (strcmp(option, "--encode") == 0) {
        return encode(input_file, output_file, argv[3]);
    } else if (strcmp(option, "--decode") == 0) {
        return decode(input_file, output_file);
    } else {
        fclose(input_file);
        fclose(output_file);
        return 4;
    }
}

int encode(FILE *input_file, FILE *output_file, char *output_file_name) {
    struct freqbook freqbook = freqbook_create();
    struct freqbook_inflater inflater = freqbook_inflater_create(&freqbook, input_file);
    freqbook_inflater_inflate(&inflater);

    struct heap heap = freqbook_to_node_heap(&freqbook);
    while (heap.size > 1) {
        struct node *first_sibling = heap_pop(&heap);
        struct node *second_sibling = heap_pop(&heap);
        int combined_freq = first_sibling->freq + second_sibling->freq;
        struct node *father = node_create(combined_freq, 0, first_sibling, second_sibling);
        heap_push(&heap, father);
    }
    struct node root = *heap_pop(&heap);

    struct codebook codebook = codebook_create();
    struct codebook_inflater cb_inflater = codebook_inflater_create(&codebook, &root);
    codebook_inflater_inflate(&cb_inflater);

    fseek(input_file, 0, SEEK_SET);
    struct encoder encoder = encoder_create(&freqbook, &codebook, input_file, output_file);
    encoder_encode(&encoder, output_file_name);

    heap_destroy(&heap);
    freqbook_destroy(&freqbook);
    freqbook_inflater_destroy(&inflater);
    codebook_destroy(&codebook);
    codebook_inflater_destroy(&cb_inflater);
    encoder_destroy(&encoder);

    return 0;
}

int decode(FILE *input_file, FILE *output_file) {
    struct decoder decoder = decoder_create(input_file, output_file);
    decoder_decode(&decoder);
    decoder_destroy(&decoder);

    return 0;
}
