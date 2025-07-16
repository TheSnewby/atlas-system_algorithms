#include "rb_trees.h"
// gcc -Wall -Wextra -Werror -pedantic 0-rb_tree_node.c 2-rb_tree_insert.c rb_tree_print.c -o rb_tree_insert -ggdb3
/**
 * tree_rotate_left - rotates a binary tree to the left
 * @tree: the passed tree or subtree
 *
 * Return: new root
 */
rb_tree_t *tree_rotate_left(rb_tree_t *tree)
{
	rb_tree_t *oldrt, *newrt, *child, *grandparent;

	if (!tree || !tree->right)
		return (NULL);

	oldrt = tree;
	newrt = tree->right;
	child = tree->right->left;
	grandparent = tree->parent;

	newrt->parent = grandparent; /* switch parents */
	oldrt->parent = newrt;

	if (grandparent) /* adjust grandparent's child */
	{
		if (grandparent->left == oldrt)
			grandparent->left = newrt;
		else
			grandparent->right = newrt;
	}

	oldrt->right = child; /* modify relationships with child */
	if (child)
		child->parent = oldrt;

	newrt->left = oldrt;


	return (newrt);
}

/**
 * tree_rotate_right - rotates a binary tree to the right
 * @tree: the passed tree or subtree
 *
 * Return: new root
 */
rb_tree_t *tree_rotate_right(rb_tree_t *tree)
{
	rb_tree_t *oldrt, *newrt, *child, *grandparent;

	if (!tree || !tree->left)
		return (NULL);

	oldrt = tree;
	newrt = tree->left;
	child = tree->left->right;
	grandparent = tree->parent;

	newrt->parent = grandparent; /* switch parents */
	oldrt->parent = newrt;

	if (grandparent) /* adjust grandparent's child */
	{
		if (grandparent->right == oldrt)
			grandparent->right = newrt;
		else
			grandparent->left = newrt;
	}

	oldrt->left = child; /* modify relationships with child */
	if (child)
		child->parent = oldrt;

	newrt->right = oldrt;

	return (newrt);
}

/**
 * rb_color_swap - swaps colors of two nodes
 * @node1: first node
 * @node2: second node
*/
void rb_color_swap(rb_tree_t *node1, rb_tree_t *node2)
{
	rb_color_t temp = node1->color;

	node1->color = node2->color;
	node2->color = temp;
}

/**
 * rb_tree_recolor_and_rotations - recolors and rotates a node
 * @tree: target node
*/
void rb_tree_recolor_and_rotations(rb_tree_t **tree)
{
	rb_tree_t *parent = NULL, *uncle = NULL, *grandparent = NULL;
	int nodeIsLeft = 0, uncleIsLeft = 0; /* location-help for rotations */

	printf("Called: rb_tree_recolor_and_rotations\n");

	if ((*tree)->parent) /* naming for own sanity */
		parent = (*tree)->parent;
	if ((*tree)->parent->parent)
		grandparent = parent->parent;
	if (grandparent && grandparent->left != parent)
	{
		uncle = grandparent->left;
		uncleIsLeft = 1;
	}
	else if (grandparent)
		uncle = grandparent->right;
	if (parent && parent->left == (*tree))
		nodeIsLeft = 1;

	printf("uncleIsLeft: %d\nnodeIsLeft: %d\n", uncleIsLeft, nodeIsLeft);

	if (uncle && uncle->color == RED)
	{
		parent->color = BLACK;
		uncle->color = BLACK;
		if (grandparent->parent)
			grandparent->color = RED;
	}
	else if (grandparent && (!uncle || (uncle && uncle->color == BLACK)))
	{
		if (!uncleIsLeft && nodeIsLeft) /* LL */
		{
			printf("LL Rotation\n"); /* DEBUG */
			(*tree) = tree_rotate_right(grandparent);
			rb_color_swap(parent, grandparent);
		}
		else if (!uncleIsLeft && !nodeIsLeft) /* LR */
		{
			printf("LR Rotation\n"); /* DEBUG */
			(*tree) = tree_rotate_left(parent);
			(*tree) = tree_rotate_right(grandparent);
			rb_color_swap((*tree), grandparent);
		}
		else if (uncleIsLeft && !nodeIsLeft) /* RR */
		{
			printf("RR Rotation\n"); /* DEBUG */
			(*tree) = tree_rotate_left(grandparent);
			rb_color_swap(parent, grandparent);
		}
		else if (uncleIsLeft && nodeIsLeft) /* RL */
		{
			printf("RL Rotation\n"); /* DEBUG */
			(*tree) = tree_rotate_right(parent);
			(*tree) = tree_rotate_left(grandparent);
			rb_color_swap((*tree), grandparent);
		}
	}
}

/**
 * rb_tree_insert_helper - recursive helper for rb_tree_insert()
 * @tree: current node
 * @value: value to be inserted
 * @parent: parent of node
 *
 * Return: pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert_helper(rb_tree_t **tree, int value, rb_tree_t *parent)
{
	rb_tree_t *new_node;
	rb_color_t new_color = RED;

	if ((*tree)) /* DEBUG */
		printf("Currently at: %d\n", (*tree)->n);
	else
		printf("Currently at Leaf\n");

	if (!(*tree)) /* create new node at leaf */
	{
		*tree = rb_tree_node(parent, value, new_color);
		new_node = (*tree);
		printf("new leaf has parent: %d\n", parent->n); /* DEBUG */
	}
	else if ((value < (*tree)->n))
		new_node = rb_tree_insert_helper(&((*tree)->left), value, (*tree));
	else if ((value > (*tree)->n))
		new_node = rb_tree_insert_helper(&((*tree)->right), value, (*tree));
	else if ((value == (*tree)->n))
		return (NULL);

	printf("(*tree)->n in helper just before recolor_and_rotation call: %d\n", (*tree)->n);
	if ((*tree) && (*tree)->parent && (*tree)->parent->color == RED)
		rb_tree_recolor_and_rotations(tree);

	if (!new_node)
		return (NULL);

	return (new_node);
}

/**
 * rb_tree_insert - inserts a value into a red-black tree
 * @tree: root node
 * @value: value to be inserted
 *
 * Return: pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node;

	if (!(*tree))
	{
		*tree = rb_tree_node(NULL, value, BLACK);
		return (*tree);
	}

	new_node = rb_tree_insert_helper(tree, value, NULL);

	return (new_node);
}

/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
    rb_tree_t *root;
    rb_tree_t *node;

    root = NULL;
	printf("\nInserting: 98\n");
    node = rb_tree_insert(&root, 98);
    printf("Inserted: %d\n", node->n);
	fflush(stdout);
    rb_tree_print(root);
	printf("\nInserting: 402\n");
    node = rb_tree_insert(&root, 402);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 512\n");
    node = rb_tree_insert(&root, 512);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 12\n");
    node = rb_tree_insert(&root, 12);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 46\n");
    node = rb_tree_insert(&root, 46);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 128\n");
    node = rb_tree_insert(&root, 128);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 256\n");
    node = rb_tree_insert(&root, 256);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 1\n");
    node = rb_tree_insert(&root, 1);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 128\n");
    node = rb_tree_insert(&root, 128);
    printf("Node should be nil -> %p\n", (void *)node);
	printf("\nInserting: 624\n");
    node = rb_tree_insert(&root, 624);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
	printf("\nInserting: 780\n");
    node = rb_tree_insert(&root, 780);
    printf("Inserted: %d\n", node->n);
    rb_tree_print(root);
    return (0);
}