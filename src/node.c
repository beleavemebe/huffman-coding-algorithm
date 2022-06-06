//
// Created by Roman on 03-Jun-22.
//

#include "../include/node.h"
#include <stdlib.h>
#include <string.h>

struct node *node_create(
    int freq,
    char value,
    struct node *left,
    struct node *right
) {
    struct node node = {
        .freq = freq,
        .value = value,
        .left = left,
        .right = right
    };

    struct node *ptr = (struct node *) calloc(1, sizeof(struct node));
    memcpy(ptr, &node, sizeof(struct node));

    return ptr;
}

void node_destroy(struct node *node) {
    node->freq = 0;
    node->value = 0;

    if (node->right != NULL) {
        node_destroy(node->right);
        free(node->right);
        node->right = NULL;
    }

    if (node->left != NULL) {
        node_destroy(node->left);
        free(node->left);
        node->left = NULL;
    }
}

int node_compare(struct node *node, struct node *other) {
    return node->freq - other->freq;
}