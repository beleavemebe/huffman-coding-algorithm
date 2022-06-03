//
// Created by Roman on 03-Jun-22.
//
#include "..\include\node.h"
#include "test.h"

#pragma FIXTURE_START

FIXTURE(Leaf_node_fixture) {
    struct node *node;
};

FIXTURE_SETUP(Leaf_node_fixture) {
    T_ node = node_create(0, 0, NULL, NULL);
}   

FIXTURE_TEARDOWN(Leaf_node_fixture) {
    node_destroy(T_ node);
}

FIXTURE(Root_node_fixture) {
    struct node *node;
};

FIXTURE_SETUP(Root_node_fixture) {
    struct node *left = node_create(0, 0, NULL, NULL);
    struct node *right = node_create(0, 0, NULL, NULL);
    T_ node = node_create(0, 0, left, right);
}

FIXTURE_TEARDOWN(Root_node_fixture) {
    node_destroy(T_ node);
}

#pragma FIXTURE_END

#pragma TEST_START

TEST(leaf_node_create_works, Leaf_node_fixture) {
    ASSERT_EQ(T_ node->value, 0, "%d");
    ASSERT_EQ(T_ node->freq, 0, "%d");
    ASSERT_NULL(T_ node->right);
    ASSERT_NULL(T_ node->left);
}

TEST(root_node_create_works, Root_node_fixture) {
    ASSERT_EQ(T_ node->value, 0, "%d");
    ASSERT_EQ(T_ node->freq, 0, "%d");
    ASSERT_NON_NULL(T_ node->right);
    ASSERT_NON_NULL(T_ node->left);
}

TEST(root_node_destroy_deallocates, Root_node_fixture) {
    node_destroy(T_ node);
    ASSERT_NULL(T_ node->left);
    ASSERT_NULL(T_ node->right);
}

#pragma TEST_END
