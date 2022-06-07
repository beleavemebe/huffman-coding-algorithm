//
// Created by Roman on 06-Jun-22.
//
#include "..\include\freqbook.h"
#include "..\include\heap.h"
#include "test.h"

#pragma FIXTURE_START

FIXTURE(Freqbook_fixture) {
    struct freqbook freqbook;
};

FIXTURE_SETUP(Freqbook_fixture) {
    T_ freqbook = freqbook_create();
}

FIXTURE_TEARDOWN(Freqbook_fixture) {
    freqbook_destroy(&T_ freqbook);
}

#pragma FIXTURE_END
#pragma TEST_START

TEST(freqbook_create_works, Freqbook_fixture) {
    ASSERT_NON_NULL(T_ freqbook.frequencies);
    for (int i = 0; i < 256; ++i) {
        ASSERT_EQ(T_ freqbook.frequencies[i], 0, "%d");
    }
}

TEST(freqbook_destroy_deallocates, Freqbook_fixture) {
    freqbook_destroy(&T_ freqbook);
}

TEST(freqbook_get_frequency_works, Freqbook_fixture) {
    T_ freqbook.frequencies[32] = 25;
    T_ freqbook.frequencies[255] = 6;
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, (char) 32), 25, "%c");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, (char) 255), 6, "%c");
}

TEST(freqbook_increase_frequency_works, Freqbook_fixture) {
    int freqA = 25;
    for (int i = 0; i < freqA; ++i) {
        freqbook_inc_freq(&T_ freqbook, 'A');
    }

    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'A'), freqA, "%d");
}

TEST(freqbook_to_heap_works, Freqbook_fixture) {
    int freqA = 25;
    for (int i = 0; i < freqA; ++i) {
        freqbook_inc_freq(&T_ freqbook, 'A');
    }

    int freqB = 21;
    for (int i = 0; i < freqB; ++i) {
        freqbook_inc_freq(&T_ freqbook, 'B');
    }

    int freqC = 2;
    for (int i = 0; i < freqC; ++i) {
        freqbook_inc_freq(&T_ freqbook, 'C');
    }

    int freqD = 245;
    for (int i = 0; i < freqD; ++i) {
        freqbook_inc_freq(&T_ freqbook, 'D');
    }

    int freqE = 1;
    for (int i = 0; i < freqE; ++i) {
        freqbook_inc_freq(&T_ freqbook, 'E');
    }

    struct heap heap = freqbook_to_node_heap(&T_ freqbook);
    int a; // line for debug breakpoint
}

TEST(freqbbook_digest_string_works, Freqbook_fixture) {
    char *string = "robin bobin barabek";
    freqbook_digest_string(&T_ freqbook, string);
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'r'), 2, "%d");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'o'), 2, "%d");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'b'), 5, "%d");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'i'), 2, "%d");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'n'), 2, "%d");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'a'), 2, "%d");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'e'), 1, "%d");
    ASSERT_EQ(freqbook_get_freq(&T_ freqbook, 'k'), 1, "%d");
}


#pragma TEST_END
