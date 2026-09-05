#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <stddef.h>

typedef struct TreeNode{

    int value;
    struct TreeNode *left;
    struct TreeNode *right;

}TreeNode;

typedef struct {
    
    TreeNode *root;
    size_t size;

}BinarySearchTree;

typedef void (*BSTVisitFunction)(int value);

int bst_init(BinarySearchTree *tree);

int bst_insert(BinarySearchTree *tree, int value);

int bst_contains(const BinarySearchTree *tree, int value);

int bst_remove(BinarySearchTree *tree, int value);

size_t bst_size(const BinarySearchTree *tree);

void bst_free(BinarySearchTree *tree);

void bst_inorder(const BinarySearchTree *tree, BSTVisitFunction visit);

void bst_preorder(const BinarySearchTree *tree, BSTVisitFunction visit);

void bst_postorder(const BinarySearchTree *tree, BSTVisitFunction visit);

#endif
