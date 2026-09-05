#include <assert.h>
#include <stdio.h>
#include "binary_search_tree.h"

/*
 * Used by traversal callbacks.
 * Since BSTVisitFunction only accepts an int,
 * we use static storage to capture traversal results.
 */
#define MAX_VISITED_VALUES 64

static int visited_values[MAX_VISITED_VALUES];
static size_t visited_count = 0;

static void reset_visited(void)
{
    visited_count = 0;
}

static void capture_value(int value)
{
    assert(visited_count < MAX_VISITED_VALUES);

    visited_values[visited_count] = value;
    visited_count++;
}

static void assert_visited_equals(
    const int *expected,
    size_t expected_count)
{
    assert(visited_count == expected_count);

    for (size_t i = 0; i < expected_count; i++)
    {
        assert(visited_values[i] == expected[i]);
    }
}

static void test_init(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(tree.root == NULL);
    assert(tree.size == 0);
    assert(bst_size(&tree) == 0);

    assert(bst_init(NULL) == -1);
    assert(bst_size(NULL) == 0);

    bst_free(&tree);
}

static void test_insert(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 20) == 0);
    assert(bst_insert(&tree, 40) == 0);
    assert(bst_insert(&tree, 60) == 0);
    assert(bst_insert(&tree, 80) == 0);

    /*
     * Expected:
     *
     *         50
     *       /    \
     *     30      70
     *    /  \    /  \
     *   20  40  60  80
     */

    assert(bst_size(&tree) == 7);

    assert(tree.root != NULL);
    assert(tree.root->value == 50);

    assert(tree.root->left != NULL);
    assert(tree.root->left->value == 30);

    assert(tree.root->right != NULL);
    assert(tree.root->right->value == 70);

    assert(tree.root->left->left != NULL);
    assert(tree.root->left->left->value == 20);

    assert(tree.root->left->right != NULL);
    assert(tree.root->left->right->value == 40);

    assert(tree.root->right->left != NULL);
    assert(tree.root->right->left->value == 60);

    assert(tree.root->right->right != NULL);
    assert(tree.root->right->right->value == 80);

    bst_free(&tree);
}

static void test_insert_invalid(void)
{
    assert(bst_insert(NULL, 10) == -1);
}

static void test_duplicate_insert(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);

    assert(bst_size(&tree) == 2);

    assert(bst_insert(&tree, 30) == -1);

    /*
     * Duplicate insertion must not change size.
     */
    assert(bst_size(&tree) == 2);

    assert(bst_contains(&tree, 30) == 1);

    bst_free(&tree);
}

static void test_contains(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    /*
     * Empty tree is valid.
     */
    assert(bst_contains(&tree, 50) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 20) == 0);
    assert(bst_insert(&tree, 40) == 0);

    assert(bst_contains(&tree, 50) == 1);
    assert(bst_contains(&tree, 30) == 1);
    assert(bst_contains(&tree, 70) == 1);
    assert(bst_contains(&tree, 20) == 1);
    assert(bst_contains(&tree, 40) == 1);

    assert(bst_contains(&tree, 35) == 0);
    assert(bst_contains(&tree, 100) == 0);

    assert(bst_contains(NULL, 50) == -1);

    bst_free(&tree);
}

static void test_remove_leaf(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 20) == 0);

    /*
     * Before:
     *
     *       50
     *      /  \
     *    30    70
     *   /
     *  20
     *
     * Remove 20.
     */

    assert(bst_remove(&tree, 20) == 0);

    assert(bst_contains(&tree, 20) == 0);
    assert(bst_size(&tree) == 3);
    assert(tree.root->left->left == NULL);

    bst_free(&tree);
}

static void test_remove_node_with_left_child(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 20) == 0);

    /*
     * Before:
     *
     *      50
     *     /
     *   30
     *   /
     * 20
     *
     * Remove 30.
     *
     * After:
     *
     *      50
     *     /
     *   20
     */

    assert(bst_remove(&tree, 30) == 0);

    assert(bst_contains(&tree, 30) == 0);
    assert(bst_contains(&tree, 20) == 1);

    assert(tree.root->left != NULL);
    assert(tree.root->left->value == 20);

    assert(bst_size(&tree) == 2);

    bst_free(&tree);
}

static void test_remove_node_with_right_child(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 40) == 0);

    /*
     * Before:
     *
     *      50
     *     /
     *   30
     *     \
     *      40
     *
     * Remove 30.
     *
     * After:
     *
     *      50
     *     /
     *   40
     */

    assert(bst_remove(&tree, 30) == 0);

    assert(bst_contains(&tree, 30) == 0);
    assert(bst_contains(&tree, 40) == 1);

    assert(tree.root->left != NULL);
    assert(tree.root->left->value == 40);

    assert(bst_size(&tree) == 2);

    bst_free(&tree);
}

static void test_remove_root_only_node(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);

    assert(bst_remove(&tree, 50) == 0);

    assert(tree.root == NULL);
    assert(bst_size(&tree) == 0);
    assert(bst_contains(&tree, 50) == 0);

    bst_free(&tree);
}

static void test_remove_root_with_one_child(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);

    /*
     * Before:
     *
     *    50
     *   /
     * 30
     *
     * Remove 50.
     *
     * After:
     *
     * 30
     */

    assert(bst_remove(&tree, 50) == 0);

    assert(tree.root != NULL);
    assert(tree.root->value == 30);

    assert(bst_size(&tree) == 1);
    assert(bst_contains(&tree, 50) == 0);
    assert(bst_contains(&tree, 30) == 1);

    bst_free(&tree);
}

static void test_remove_two_children(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 20) == 0);
    assert(bst_insert(&tree, 40) == 0);
    assert(bst_insert(&tree, 60) == 0);
    assert(bst_insert(&tree, 80) == 0);

    /*
     * Remove 30.
     *
     * 30 has:
     *
     * left  = 20
     * right = 40
     *
     * Its inorder successor is 40.
     */

    assert(bst_remove(&tree, 30) == 0);

    assert(bst_contains(&tree, 30) == 0);
    assert(bst_contains(&tree, 20) == 1);
    assert(bst_contains(&tree, 40) == 1);

    assert(bst_size(&tree) == 6);

    /*
     * 40 should replace 30.
     */
    assert(tree.root->left != NULL);
    assert(tree.root->left->value == 40);
    assert(tree.root->left->left != NULL);
    assert(tree.root->left->left->value == 20);

    bst_free(&tree);
}

static void test_remove_root_with_two_children(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 60) == 0);
    assert(bst_insert(&tree, 80) == 0);

    /*
     * Before:
     *
     *       50
     *      /  \
     *    30    70
     *         /  \
     *        60  80
     *
     * Inorder successor of 50 is 60.
     */

    assert(bst_remove(&tree, 50) == 0);

    assert(bst_contains(&tree, 50) == 0);

    assert(tree.root != NULL);
    assert(tree.root->value == 60);

    assert(bst_contains(&tree, 30) == 1);
    assert(bst_contains(&tree, 70) == 1);
    assert(bst_contains(&tree, 80) == 1);

    assert(bst_size(&tree) == 4);

    bst_free(&tree);
}

static void test_remove_successor_with_right_child(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    /*
     * Build:
     *
     *         50
     *       /    \
     *     30      80
     *            /
     *           60
     *             \
     *              70
     *
     * Removing 50:
     *
     * successor = 60
     *
     * successor itself has a right child, 70.
     * The implementation must reconnect 70 correctly.
     */

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 80) == 0);
    assert(bst_insert(&tree, 60) == 0);
    assert(bst_insert(&tree, 70) == 0);

    assert(bst_remove(&tree, 50) == 0);

    assert(tree.root != NULL);
    assert(tree.root->value == 60);

    assert(bst_contains(&tree, 50) == 0);
    assert(bst_contains(&tree, 60) == 1);
    assert(bst_contains(&tree, 70) == 1);
    assert(bst_contains(&tree, 80) == 1);

    assert(tree.root->right != NULL);
    assert(tree.root->right->value == 80);

    assert(tree.root->right->left != NULL);
    assert(tree.root->right->left->value == 70);

    assert(bst_size(&tree) == 4);

    bst_free(&tree);
}

static void test_remove_missing_value(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);

    assert(bst_remove(&tree, 999) == -1);

    /*
     * Tree must remain unchanged.
     */
    assert(bst_size(&tree) == 3);

    assert(bst_contains(&tree, 50) == 1);
    assert(bst_contains(&tree, 30) == 1);
    assert(bst_contains(&tree, 70) == 1);

    bst_free(&tree);
}

static void test_remove_invalid(void)
{
    BinarySearchTree tree;

    assert(bst_remove(NULL, 50) == -1);

    assert(bst_init(&tree) == 0);

    /*
     * Removing from an empty valid tree.
     */
    assert(bst_remove(&tree, 50) == -1);

    bst_free(&tree);
}

static void test_inorder(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 20) == 0);
    assert(bst_insert(&tree, 40) == 0);
    assert(bst_insert(&tree, 60) == 0);
    assert(bst_insert(&tree, 80) == 0);

    const int expected[] = {
        20,
        30,
        40,
        50,
        60,
        70,
        80
    };

    reset_visited();

    bst_inorder(&tree, capture_value);

    assert_visited_equals(
        expected,
        sizeof(expected) / sizeof(expected[0]));

    bst_free(&tree);
}

static void test_preorder(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 20) == 0);
    assert(bst_insert(&tree, 40) == 0);
    assert(bst_insert(&tree, 60) == 0);
    assert(bst_insert(&tree, 80) == 0);

    const int expected[] = {
        50,
        30,
        20,
        40,
        70,
        60,
        80
    };

    reset_visited();

    bst_preorder(&tree, capture_value);

    assert_visited_equals(
        expected,
        sizeof(expected) / sizeof(expected[0]));

    bst_free(&tree);
}

static void test_postorder(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);
    assert(bst_insert(&tree, 20) == 0);
    assert(bst_insert(&tree, 40) == 0);
    assert(bst_insert(&tree, 60) == 0);
    assert(bst_insert(&tree, 80) == 0);

    const int expected[] = {
        20,
        40,
        30,
        60,
        80,
        70,
        50
    };

    reset_visited();

    bst_postorder(&tree, capture_value);

    assert_visited_equals(
        expected,
        sizeof(expected) / sizeof(expected[0]));

    bst_free(&tree);
}

static void test_traversal_empty_tree(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    reset_visited();

    bst_inorder(&tree, capture_value);
    assert(visited_count == 0);

    bst_preorder(&tree, capture_value);
    assert(visited_count == 0);

    bst_postorder(&tree, capture_value);
    assert(visited_count == 0);

    bst_free(&tree);
}

static void test_traversal_invalid_arguments(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);
    assert(bst_insert(&tree, 50) == 0);

    /*
     * These should safely return without crashing.
     */
    bst_inorder(NULL, capture_value);
    bst_inorder(&tree, NULL);

    bst_preorder(NULL, capture_value);
    bst_preorder(&tree, NULL);

    bst_postorder(NULL, capture_value);
    bst_postorder(&tree, NULL);

    bst_free(&tree);
}

static void test_free(void)
{
    BinarySearchTree tree;

    assert(bst_init(&tree) == 0);

    assert(bst_insert(&tree, 50) == 0);
    assert(bst_insert(&tree, 30) == 0);
    assert(bst_insert(&tree, 70) == 0);

    assert(bst_size(&tree) == 3);

    bst_free(&tree);

    assert(tree.root == NULL);
    assert(tree.size == 0);
    assert(bst_size(&tree) == 0);

    /*
     * Must safely accept NULL.
     */
    bst_free(NULL);
}

int main(void)
{
    test_init();

    test_insert();
    test_insert_invalid();
    test_duplicate_insert();

    test_contains();

    test_remove_leaf();
    test_remove_node_with_left_child();
    test_remove_node_with_right_child();
    test_remove_root_only_node();
    test_remove_root_with_one_child();
    test_remove_two_children();
    test_remove_root_with_two_children();
    test_remove_successor_with_right_child();
    test_remove_missing_value();
    test_remove_invalid();

    test_inorder();
    test_preorder();
    test_postorder();
    test_traversal_empty_tree();
    test_traversal_invalid_arguments();

    test_free();

    printf("All binary search tree tests passed.\n");

    return 0;
}