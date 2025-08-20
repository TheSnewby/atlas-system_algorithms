#include "nary_trees.h"

/**
 * biggest_depth_helper - recursive helper for biggest_depth
 * @node: current node of the tree
 *
 * Return: biggest depth of the tree pointed to by the root
 */
size_t biggest_depth_helper(nary_tree_t const *node)
{
	size_t dep_children, dep_next, bd;

	if (!node)
		return (0);

	dep_children = biggest_depth_helper(node->children);
	dep_next = biggest_depth_helper(node->next);
	if (node->children)
		dep_children++;
	bd = (dep_children > dep_next) ? dep_children : dep_next;

	return (bd);
}

/**
 * biggest_depth - find largest depth (current height) of a node
 * @node: current node of the tree
 *
 * Return: biggest depth of the tree pointed to by the root
 */
size_t biggest_depth(nary_tree_t const *node)
{
	size_t bd;

	if (!node)
		return (0);

	bd = biggest_depth_helper(node->children);
	return (bd + 1);
}

/**
 * nary_tree_diameter - computes the diameter of an N-ary tree
 * @root: root node
 *
 * Return: diamater of the tree
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t first = 0, second = 0, retValue = 0;
	nary_tree_t *temp = root->children;

	if (!root)
		return (0);

	while (temp)
	{
		retValue = biggest_depth(temp);
		if (retValue > first)
		{
			second = first;
			first = retValue;
		}
		else if (retValue > second)
			second = retValue;
		temp = temp->next;
	}

	if (first && second)
		return (first + second + 2);
	else if (first)
		return (first + 1);
	else
		return (0);
}
