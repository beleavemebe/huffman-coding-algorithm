//
// Created by Roman on 02-Jun-22.
//
#include <stdbool.h>

#ifndef HUFFMAN_HEAP_H
#define HUFFMAN_HEAP_H

#define HEAP_INITIAL_CAPACITY 10
#define HEAP_CAPACITY_MULTIPLIER 2

struct heap {
    int size;
    int capacity;
    struct node *nodes;
};


struct heap heap_create();
void heap_destroy(struct heap* heap);
bool heap_is_empty(struct heap *heap);
struct node heap_pop(struct heap *heap);
void heap_push(struct heap* heap, struct node* node);

#endif //HUFFMAN_HEAP_H
