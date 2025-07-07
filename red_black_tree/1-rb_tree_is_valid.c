#include "rb_trees.h"

/**
 * rb_tree_valid_recurse - recursive check for whether a tree is a valid RBT
 * @tree: root node to tree
 * @min: minimum allowed R Value
 * @max: maximum allowed L Value
 *
 * Return: 1 if valid RBT, 0 otherwise
 */
int rb_tree_valid_recurse(rb_tree_t *tree, int min, int max)
{
	int left_return = 1, right_return = 1;

	if ((tree->color == RED) && (tree->parent->color == RED))
		return (0);
	if (!(tree->color == RED || tree->color == BLACK))
		return (0);

	if (tree->left)
	{
		if ((tree->color == RED) && (tree->left->color == RED))
			return (0);
		if ((tree->left->n < tree -> n) && (tree->left->n > min))
		{
			left_return = rb_tree_valid_recurse(tree->left, min, tree->n);
		}
		else
			return (0);
	}
	if (tree->right)
	{
		if ((tree->color == RED) && (tree->right->color == RED))
			return (0);
		if ((tree->right->n > tree->n) && (tree->right->n < max))
		{
			right_return = rb_tree_valid_recurse(tree->right, tree->n, max);
		}
		else
			return (0);
	}
	return (left_return * right_return);
}

/**
 * rb_tree_is_valid - checks if a binary tree is a valid Red-Black Tree
 * @tree: root node of the tree to check
 *
 * Return: 1 if valid, 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int min, max;

	if (!tree || tree->color == RED)
		return (0);

	min = INT_MIN;
	max = INT_MAX;

	return (rb_tree_valid_recurse(tree, min, max));
}
