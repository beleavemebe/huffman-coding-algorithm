//
// Created by Roman on 03-Jun-22.
//
#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

struct node {
    int freq;
    char value;
    struct node *left;
    struct node *right;
};

struct node *node_create(int freq, char value, struct node *left, struct node *right);
void node_destroy(struct node *node);

#endif //HUFFMAN_NODE_H
