//
// Created by Roman on 08-Jun-22.
//

#include <string.h>
#include <stdlib.h>
#include "../include/codebook.h"

struct codebook codebook_create() {
    return (struct codebook) {
        .codes = calloc(256, sizeof(char))
    };
}

void codebook_destroy(struct codebook *codebook) {
    free(codebook->codes);
    codebook->codes = NULL;
}

char codebook_get_code(struct codebook *codebook, char c) {
    return codebook->codes[(unsigned char) c];
}

void codebook_set_code(struct codebook *codebook, char c, char code) {
    codebook->codes[(unsigned char) c] = code;
}
