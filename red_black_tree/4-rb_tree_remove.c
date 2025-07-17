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
 * rb_tree_recolor_and_rotations_pt2 - continues recoloring and rotation
 * @tree: target node
 * @parent: parent of target node
 * @grandparent: grandparent of target node
 * @nodeIsLeft: bool of whether target node is a left child
 * @uncleIsLeft: bool of whether uncle of target node is a left child
 *
 * Return: current node
 */
rb_tree_t *rb_tree_recolor_and_rotations_pt2(rb_tree_t **tree,
	rb_tree_t *parent, rb_tree_t *grandparent,
	int nodeIsLeft, int uncleIsLeft)
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

	return (*tree);
}

/**
 * rb_tree_recolor_and_rotations - recolors and rotates a node
 * @tree: target node
 *
 * Return: current node
*/
rb_tree_t *rb_tree_recolor_and_rotations(rb_tree_t **tree)
{
	rb_tree_t *parent = NULL, *uncle = NULL, *grandparent = NULL;
	int nodeIsLeft = 0, uncleIsLeft = 0; /* location-help for rotations */

	if ((*tree)->parent) /* naming for own sanity */
		parent = (*tree)->parent;
	if (parent && parent->parent)
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

	if (uncle && uncle->color == RED)
	{
		parent->color = BLACK;
		uncle->color = BLACK;
		if (grandparent->parent)
			grandparent->color = RED;
		*tree = grandparent;
	}
	else if (grandparent && (!uncle || (uncle && uncle->color == BLACK)))
		*tree = rb_tree_recolor_and_rotations_pt2(tree, parent, grandparent,
			nodeIsLeft, uncleIsLeft);

	return (*tree);
}

/**
 * rb_tree_remove_helper - recursive helper for rb_tree_remove()
 * @root: root of red-black tree
 * @n: value to be removed
 *
 * Return: root of red-black tree
 */
rb_tree_t *rb_tree_remove_helper(rb_tree_t **root, int n)
{
	if (!(*root))
		return (*root);
}

/**
 * rb_tree_remove - removes a node from a red-black tree
 * @root: root of red-black tree
 * @n: value to be removed
 *
 * Return: pointer to root
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *temp;

	if (!root)
		return (NULL);

	root = rb_tree_remove_helper(&root, n);

	temp = root;

	while ((temp) && (temp)->parent && temp->parent->color == RED)
		temp = rb_tree_recolor_and_rotations(&temp);

	while (temp->parent)
		temp = temp->parent;

	(root) = temp;
	(root)->color = BLACK;

	return (root);
}
