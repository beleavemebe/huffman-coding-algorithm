//
// Created by Roman on 08-Jun-22.
//

#ifndef HUFFMAN_CODEBOOK_H
#define HUFFMAN_CODEBOOK_H

#define CODEBOOK_SIZE 256

struct codebook {
    char **codes;
};

struct codebook codebook_create();
void codebook_destroy(struct codebook *codebook);
char *codebook_get_code(struct codebook *codebook, char c);
void codebook_set_code(struct codebook *codebook, char c, char *code);
int codebook_get_longest_code_length(struct codebook *codebook);

struct codebook_inflater {
    struct codebook *codebook;
    struct node *tree_root;
};

struct codebook_inflater codebook_inflater_create(struct codebook *codebook, struct node *tree_root);
void codebook_inflater_destroy(struct codebook_inflater *inflater);
void codebook_inflater_inflate(struct codebook_inflater *inflater);

#endif //HUFFMAN_CODEBOOK_H
