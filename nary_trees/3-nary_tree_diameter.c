#include "nary_trees.h"
/**
 * ntd_helper - recursive helper for nary_tree_diameter
 * @node: Current node in tree
 *
 * Return: metrics of the subtree
 */
metrics_t ntd_helper(nary_tree_t const *node)
{
	metrics_t current_metrics = {1, 1}, child_metrics;
	size_t first_height = 0, second_height = 0;
	size_t max_child_d = 1; /* tracks whether longest diam is from single path */
	nary_tree_t const *child;

	if (!node)
		return ((metrics_t){0, 0});

	child = node->children; /* traverse children of node */
	while (child)
	{
		child_metrics = ntd_helper(child);

		if (child_metrics.diameter > max_child_d)
			max_child_d = child_metrics.diameter;

		if (child_metrics.height + 1 > first_height) /* +1 for current node*/
		{
			second_height = first_height;
			first_height = child_metrics.height + 1;
		}
		else if (child_metrics.height + 1 > second_height)
			second_height = child_metrics.height + 1;

		child = child->next;
	}
	current_metrics.height = first_height ? first_height : 1;
	current_metrics.diameter = max_child_d;
	if (first_height && second_height)
	{
		if (first_height + second_height - 1 > current_metrics.diameter)
			current_metrics.diameter = first_height + second_height - 1;
	}
	else if (first_height)
	{
		if (first_height + 1 > current_metrics.diameter)
			current_metrics.diameter = first_height + 1;
	}

	return (current_metrics);
}


/**
 * nary_tree_diameter - computes the diameter of an N-ary tree, the diamater is
 * calculated as the number of nodes, not edges, of the longest path
 * @root: root node
 *
 * Return: diamater of the tree
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	if (!root)
		return (0);

	return (ntd_helper(root).diameter);
}
