//
// Created by Roman on 02-Jun-22.
//
#include "..\include\heap.h"
#include "test.h"
#include <stdbool.h>

#pragma FIXTURE_START

FIXTURE(Heap_fixture) {
    struct heap heap;
};

FIXTURE_SETUP(Heap_fixture) {
    T_ heap = heap_create();
}

FIXTURE_TEARDOWN(Heap_fixture) {
    heap_destroy(&T_ heap);
}

#pragma FIXTURE_END

#pragma TEST_START

TEST(heap_create_works, Heap_fixture) {
    ASSERT_NON_NULL(T_ heap.items);
    ASSERT_EQ(T_ heap.capacity, HEAP_INITIAL_CAPACITY, "%zu");
    ASSERT_EQ(T_ heap.size, 0, "%zu");
}

TEST(heap_destroy_deallocates, Heap_fixture) {
    heap_destroy(&T_ heap);
    ASSERT_NULL(T_ heap.items);
}

TEST(heap_is_empty, Heap_fixture) {
    ASSERT_EQ(heap_is_empty(&T_ heap), true, "%d");
}

TEST(heap_push_works, Heap_fixture) {
    heap_push(&T_ heap, 2);
    ASSERT_EQ(T_ heap.size, 1, "%d");
    heap_push(&T_ heap, 3);
    ASSERT_EQ(T_ heap.size, 2, "%d");
}

TEST(heap_pop_works, Heap_fixture) {
    heap_push(&T_ heap, 1);
    ASSERT_EQ(heap_pop(&T_ heap), 1, "%d");
    heap_push(&T_ heap, 3);
    heap_push(&T_ heap, 10);
    heap_push(&T_ heap, 2);
    heap_push(&T_ heap, 1);
    ASSERT_EQ(heap_pop(&T_ heap), 1, "%d");
}

#pragma TEST_END

int main() {}

