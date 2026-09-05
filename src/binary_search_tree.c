#include <stdlib.h>
#include <stddef.h>
#include "binary_search_tree.h"

int bst_init(BinarySearchTree *tree){

    if(tree == NULL){
        return -1;
    }
    tree->root = NULL;
    tree->size = 0;
    return 0;
}

int bst_insert(BinarySearchTree *tree, int value)
{
    if (tree == NULL)
        return -1;

    TreeNode *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return -1;

    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    if (tree->root == NULL)
    {
        tree->root = new_node;
        tree->size++;
        return 0;
    }

    TreeNode *current = tree->root;
    TreeNode *parent = NULL;

    while (current != NULL)
    {
        parent = current;

        if (value < current->value)
        {
            current = current->left;
        }
        else if (value > current->value)
        {
            current = current->right;
        }
        else
        {
            free(new_node);
            return -1; /* Duplicate */
        }
    }

    if (value < parent->value)
        parent->left = new_node;
    else
        parent->right = new_node;

    tree->size++;

    return 0;
}

int bst_contains(const BinarySearchTree *tree, int value)
{
    if (tree == NULL)
        return -1;

    const TreeNode *current = tree->root;

    while (current != NULL)
    {
        if (value < current->value)
            current = current->left;
        else if (value > current->value)
            current = current->right;
        else
            return 1;
    }

    return 0;
}

int bst_remove(BinarySearchTree *tree, int value)
{
    if (tree == NULL || tree->root == NULL)
        return -1;

    TreeNode *current = tree->root;
    TreeNode *parent = NULL;

    /* Find node */
    while (current != NULL && current->value != value)
    {
        parent = current;

        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
        return -1;

    /*
     * Case 1 + 2:
     * Node has zero or one child.
     */
    if (current->left == NULL || current->right == NULL)
    {
        TreeNode *child;

        if (current->left != NULL)
            child = current->left;
        else
            child = current->right;

        /*
         * Removing root.
         */
        if (parent == NULL)
        {
            tree->root = child;
        }
        else if (parent->left == current)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }

        free(current);
        tree->size--;

        return 0;
    }

    /*
     * Case 3:
     * Node has two children.
     *
     * Find smallest node in right subtree.
     */
    TreeNode *successor_parent = current;
    TreeNode *successor = current->right;

    while (successor->left != NULL)
    {
        successor_parent = successor;
        successor = successor->left;
    }

    /*
     * Copy successor's value into target node.
     */
    current->value = successor->value;

    /*
     * Remove original successor.
     * Successor can only have a right child.
     */
    if (successor_parent->left == successor)
    {
        successor_parent->left = successor->right;
    }
    else
    {
        successor_parent->right = successor->right;
    }

    free(successor);
    tree->size--;

    return 0;
}

size_t bst_size(const BinarySearchTree *tree){

    if(tree == NULL){
        return 0;
    }
    return tree->size;
}

static void free_node(TreeNode *node)
{
    if (node == NULL)
        return;

    free_node(node->left);
    free_node(node->right);

    free(node);
}

void bst_free(BinarySearchTree *tree)
{
    if (tree == NULL)
        return;

    free_node(tree->root);

    tree->root = NULL;
    tree->size = 0;
}

static void inorder_node(const TreeNode *node, BSTVisitFunction visit){

    if(node == NULL || visit == NULL){
        return;
    }

    inorder_node(node->left, visit);

    visit(node->value);

    inorder_node(node->right, visit);


}
static void preorder_node(const TreeNode *node, BSTVisitFunction visit){

    if(node == NULL || visit == NULL){
        return;
    }

    visit(node->value);

    preorder_node(node->left, visit);

    preorder_node(node->right, visit);

}
static void postorder_node(const TreeNode *node, BSTVisitFunction visit){

    if(node == NULL || visit == NULL){
        return;
    }

    postorder_node(node->left, visit);

    postorder_node(node->right, visit);

    visit(node->value);
}

void bst_inorder(const BinarySearchTree *tree, BSTVisitFunction visit){

    if(tree == NULL || visit == NULL){
        return;
    }

    inorder_node(tree->root, visit);
}

void bst_preorder(const BinarySearchTree *tree, BSTVisitFunction visit){

    if(tree == NULL || visit == NULL){
        return;
    }

    preorder_node(tree->root, visit);
}

void bst_postorder(const BinarySearchTree *tree, BSTVisitFunction visit){

    if(tree == NULL || visit == NULL){
        return;
    }

    postorder_node(tree->root, visit);
}