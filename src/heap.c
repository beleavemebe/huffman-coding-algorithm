//
// Created by Roman on 02-Jun-22.
//

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "..\include\heap.h"
#include "..\include\node.h"

struct heap heap_create() {
    struct node *items = calloc(HEAP_INITIAL_CAPACITY, sizeof(struct node));
    return (struct heap) {
        .size = 0,
        .capacity = HEAP_INITIAL_CAPACITY,
        .nodes = items
    };
}

void heap_destroy(struct heap* heap) {
    free(heap->nodes);
    heap->nodes = NULL;
}

static int heap_index_of_left_child(int index) {
    return 2 * index + 1;
}

static int heap_index_of_right_child(int index) {
    return 2 * index + 2;
}

static int heap_index_of_parent(int index) {
    return (index - 1) / 2;
}

static struct node *heap_left_child(struct heap *heap, int index) {
    return &heap->nodes[heap_index_of_left_child(index)];
}

static struct node *heap_right_child(struct heap *heap, int index) {
    return &heap->nodes[heap_index_of_right_child(index)];
}

static struct node *heap_parent(struct heap *heap, int index) {
    return &heap->nodes[heap_index_of_parent(index)];
}

static bool heap_has_left_child(struct heap *heap, int index) {
    return heap_index_of_left_child(index) < heap->size;
}

static bool heap_has_right_child(struct heap *heap, int index) {
    return heap_index_of_right_child(index) < heap->size;
}

static bool heap_has_parent(struct heap *heap, int index) {
    return heap_index_of_parent(index) >= 0;
}

static void heap_swap(struct heap *heap, int i, int j) {
    struct node temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = temp;
}

static void heap_ensure_capacity(struct heap *heap) {
    if (heap->size == heap->capacity) {
        int new_capacity = heap->capacity * HEAP_CAPACITY_MULTIPLIER;
        heap->nodes = (struct node *) realloc(heap->nodes, new_capacity * sizeof(struct node));
        heap->capacity = new_capacity;
    }
}

static void heap_heapify_down(struct heap *heap) {
    int index = 0;
    while (heap_has_left_child(heap, index)) {
        int smaller_child_index;
        int right_child_index = heap_index_of_right_child(index);
        int left_child_index = heap_index_of_left_child(index);
        if (node_compare(&heap->nodes[left_child_index], &heap->nodes[right_child_index]) < 0) {
            smaller_child_index = left_child_index;
        } else {
            smaller_child_index = right_child_index;
        }

        if (node_compare(&heap->nodes[index], &heap->nodes[smaller_child_index]) < 0) {
            break;
        } else {
            heap_swap(heap, index, smaller_child_index);
            index = smaller_child_index;
        }
    }
}

static void heap_heapify_up(struct heap *heap) {
    int index = heap->size - 1;
    while (heap_has_parent(heap, index) && node_compare(&heap->nodes[index], heap_parent(heap, index)) < 0) {
        int parent_index = heap_index_of_parent(index);
        heap_swap(heap, index, parent_index);
        index = parent_index;
    }
}

bool heap_is_empty(struct heap *heap) {
    return heap->size == 0;
}


struct node heap_pop(struct heap *heap) {
    assert(heap->size > 0);

    struct node result = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size -= 1;
    heap_heapify_down(heap);

    return result;
}

void heap_push(struct heap* heap, struct node* node) {
    heap_ensure_capacity(heap);
    heap->nodes[heap->size] = *node;
    heap->size += 1;
    heap_heapify_up(heap);
}
