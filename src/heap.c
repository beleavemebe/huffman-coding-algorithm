//
// Created by Roman on 02-Jun-22.
//

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "..\include\heap.h"

struct heap heap_create() {
    int *array = calloc(HEAP_INITIAL_CAPACITY, sizeof(int));
    return (struct heap) {
        .size = 0,
        .capacity = HEAP_INITIAL_CAPACITY,
        .items = array
    };
}

void heap_destroy(struct heap* heap) {
    free(heap->items);
    heap->items = NULL;
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

static int heap_left_child(struct heap *heap, int index) {
    return heap->items[heap_index_of_left_child(index)];
}

static int heap_right_child(struct heap *heap, int index) {
    return heap->items[heap_index_of_right_child(index)];
}

static int heap_parent(struct heap *heap, int index) {
    return heap->items[heap_index_of_parent(index)];
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
    int temp = heap->items[i];
    heap->items[i] = heap->items[j];
    heap->items[j] = temp;
}

static void heap_ensure_capacity(struct heap *heap) {
    if (heap->size == heap->capacity) {
        int new_capacity = heap->capacity * HEAP_CAPACITY_MULTIPLIER;
        heap->items = (int *) realloc(heap->items, new_capacity * sizeof(int));
        heap->capacity = new_capacity;
    }
}

static void heap_heapify_down(struct heap *heap) {
    int index = 0;
    while (heap_has_left_child(heap, index)) {
        int smaller_child_index;
        int right_child_index = heap_index_of_right_child(index);
        int left_child_index = heap_index_of_right_child(index);
        if (heap->items[left_child_index] < heap->items[right_child_index]) {
            smaller_child_index = left_child_index;
        } else {
            smaller_child_index = right_child_index;
        }

        if (heap->items[index] < heap->items[smaller_child_index]) {
            break;
        } else {
            heap_swap(heap, index, smaller_child_index);
            index = smaller_child_index;
        }
    }
}

static void heap_heapify_up(struct heap *heap) {
    int index = heap->size - 1;
    while (heap_has_parent(heap, index) && heap->items[index] < heap_parent(heap, index)) {
        int parent_index = heap_index_of_parent(index);
        heap_swap(heap, index, parent_index);
        index = parent_index;
    }
}

bool heap_is_empty(struct heap *heap) {
    return heap->size == 0;
}

int heap_pop(struct heap *heap) {
    assert(heap->size > 0);

    int result = heap->items[0];
    heap->items[0] = heap->items[heap->size - 1];
    heap->size -= 1;
    heap_heapify_down(heap);

    return result;
}

void heap_push(struct heap *heap, int item) {
    heap_ensure_capacity(heap);
    heap->items[heap->size] = item;
    heap->size += 1;
    heap_heapify_up(heap);
}
