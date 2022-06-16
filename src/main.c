#include <stdio.h>
#include "../include/freqbook.h"
#include "../include/node.h"
#include "../include/heap.h"
#include "../include/codebook.h"
#include "../include/encoder.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage %s <input filename> <output filename>\n", argv);
        return 1;
    } else if (argc < 3) {
        printf("Usage %s <output filename>\n", argv);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Could not open input file %s\n", argv[1]);
        return 2;
    }

    struct freqbook freqbook = freqbook_create();
    struct freqbook_inflater inflater = freqbook_inflater_create(&freqbook, file);
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

    fseek(file, 0, SEEK_SET);

    FILE *output_file = fopen(argv[2], "ab");
    if (output_file == NULL) {
        printf("Could not open output file %s\n", argv[2]);
        return 3;
    }

    struct encoder encoder = encoder_create(&codebook, file, output_file);
    encoder_encode(&encoder);

    heap_destroy(&heap);
    freqbook_destroy(&freqbook);
    freqbook_inflater_destroy(&inflater);
    codebook_destroy(&codebook);
    codebook_inflater_destroy(&cb_inflater);
    encoder_destroy(&encoder);

    fclose(file);

    return 0;
}
