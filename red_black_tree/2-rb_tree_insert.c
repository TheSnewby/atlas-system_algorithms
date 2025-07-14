#include "rb_trees.h"

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

	if ((*tree)->parent && (*tree)->parent->parent) /* naming for own sanity */
	{
		parent = (*tree)->parent;
		grandparent = parent->parent;
	}
	if (grandparent && grandparent->left != parent) /* more naming */
	{
		uncle = grandparent->left;
		uncleIsLeft = 1;
	}
	else
		uncle = grandparent->right;
	if (parent && parent->left == (*tree))
		nodeIsLeft = 1;

	if (parent->color == RED && grandparent && uncle->color == RED)
	{
		parent->color = BLACK;
		uncle->color = BLACK;
		if (grandparent->parent)
			grandparent->color = RED;
	}
	else if (parent->color == RED && grandparent && uncle->color == BLACK)
	{
		if (!uncleIsLeft && nodeIsLeft) /* LL */
		{
			tree_rotate_right(grandparent);
			rb_color_swap(parent, grandparent);
		}
		else if (!uncleIsLeft && !nodeIsLeft) /* LR */
		{
			tree_rotate_left(parent);
			tree_rotate_right(grandparent);
			rb_color_swap((*tree), grandparent);
		}
		else if (uncleIsLeft && !nodeIsLeft) /* RR */
		{
			tree_rotate_left(grandparent);
			rb_color_swap(parent, grandparent);
		}
		else if (uncleIsLeft && nodeIsLeft) /* RL */
		{
			tree_rotate_right(parent);
			tree_rotate_left(grandparent);
			rb_color_swap((*tree), grandparent);
		}
	}
}

/**
 * rb_tree_insert_helper - recursive helper for rb_tree_insert()
 * @tree: current node
 * @value: value to be inserted
 * @parent: parent of current node
 *
 * Return: pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert_helper(rb_tree_t **tree, int value, rb_tree_t *parent)
{
	rb_tree_t *new_node, *parent, *uncle, *grandparent;
	rb_color_t new_color = RED;

	if ((*tree) && (value < (*tree)->n))
	{
		new_node = rb_tree_insert_helper(&((*tree)->left), value, (*tree)->parent);
		if (new_node && (*tree)->left)
			(*tree)->left->parent = *tree;
	}
	else if ((*tree) && (value > (*tree)->n))
	{
		new_node = rb_tree_insert_helper(&((*tree)->right), value, (*tree)->parent);
		if (new_node && (*tree)->right)
			(*tree)->right->parent = *tree;
	}
	else if ((*tree) && (value == (*tree)->n))
		return (NULL);
	else if (!(*tree)) /* create new node at leaf */
		*tree = rb_tree_node(NULL, value, new_color);

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

	new_node = rb_tree_insert_helper(tree, value, (*tree)->parent);

	return (new_node);
}
