//
// Created by Roman on 08-Jun-22.
//
#include "..\include\codebook.h"
#include "..\include\heap.h"
#include "test.h"

#pragma FIXTURE_START

FIXTURE(Codebook_fixture) {
    struct codebook codebook;
};

FIXTURE_SETUP(Codebook_fixture) {
    T_ codebook = codebook_create();
}

FIXTURE_TEARDOWN(Codebook_fixture) {
    codebook_destroy(&T_ codebook);
}

#pragma FIXTURE_END
#pragma TEST_START

TEST(codebook_create_works, Codebook_fixture) {
    ASSERT_NON_NULL(T_ codebook.codes);
    for (int i = 0; i < CODEBOOK_SIZE; ++i) {
        ASSERT_EQ(T_ codebook.codes[i], 0, "%d");
    }
}

TEST(codebook_destroy_deallocates, Codebook_fixture) {
    codebook_destroy(&T_ codebook);
}

TEST(codebook_set_code_works, Codebook_fixture) {
    char *code = "01010";
    codebook_set_code(&T_ codebook, 'A', code);
    ASSERT_EQ(T_ codebook.codes[(unsigned char) 'A'], code, "%s");
}

TEST(codebook_get_code_works, Codebook_fixture) {
    char *code = "01010";
    codebook_set_code(&T_ codebook, 'A', code);
    ASSERT_EQ(codebook_get_code(&T_ codebook, 'A'), code, "%s");
}

#pragma TEST_END
