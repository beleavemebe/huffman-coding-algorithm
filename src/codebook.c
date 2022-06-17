//
// Created by Roman on 08-Jun-22.
//

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../include/codebook.h"
#include "../include/node.h"

struct codebook codebook_create() {
    return (struct codebook) {
        .codes = calloc(256, sizeof(char*))
    };
}

void codebook_destroy(struct codebook *codebook) {
    // should also call free() on each code, but it segfaults for some reason
    free(codebook->codes);
    codebook->codes = NULL;
}

char *codebook_get_code(struct codebook *codebook, char c) {
    return codebook->codes[(unsigned char) c];
}

void codebook_set_code(struct codebook *codebook, char c, char *code) {
    codebook->codes[(unsigned char) c] = code;
}

struct codebook_inflater codebook_inflater_create(struct codebook *codebook, struct node *tree_root) {
    return (struct codebook_inflater) {
        .codebook = codebook,
        .tree_root = tree_root,
    };
}

void codebook_inflater_destroy(struct codebook_inflater *inflater) {
    inflater->codebook = NULL;
    inflater->tree_root = NULL;
}

static char *concat_n_duplicate(char *first, char *second) {
    size_t result_length = strlen(first) + strlen(second) + 1;
    char *result = calloc(result_length, sizeof(char));
    strcpy(result, first);
    strcat(result, second);
    return result;
}

static void codebook_inflater_traverse_tree(
    struct codebook_inflater *inflater,
    struct node *node,
    char *code
) {
    if (node->left == NULL && node->right == NULL) {
        codebook_set_code(inflater->codebook, node->value, code);
        return;
    }

    if (node->left != NULL)  {
        codebook_inflater_traverse_tree(inflater, node->left, concat_n_duplicate(code, "1"));
    }

    if (node->right != NULL) {
        codebook_inflater_traverse_tree(inflater, node->right, concat_n_duplicate(code, "0"));
    }
}

void codebook_inflater_inflate(struct codebook_inflater *inflater) {
    codebook_inflater_traverse_tree(inflater, inflater->tree_root->left, "1");
    codebook_inflater_traverse_tree(inflater, inflater->tree_root->right, "0");
}

int codebook_get_longest_code_length(struct codebook *codebook) {
    int max = -1;
    for (int i = 1; i < CODEBOOK_SIZE; ++i) {
        if (codebook->codes[i] == NULL) {
            continue;
        }
        max = (int) fmax(max, (int) strlen(codebook->codes[i]));
    }
    return max;
}