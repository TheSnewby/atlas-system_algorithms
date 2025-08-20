#include "nary_trees.h"

/**
 * ntt_helper - recursive helper for nary_tree_travers
 * @node: current node of the tree
 * @action: function pointer to execute for each node traversed
 *  - node: node being traversed
 *  - depth: depth of the node being traversed
 * @depth: current depth
 *
 * Return: biggest depth of the tree pointed to by the root
 */
size_t ntt_helper(nary_tree_t const *node,
	void (*action)(nary_tree_t const *node, size_t depth), size_t depth)
{
	size_t dep_children, dep_next, bd;

	if (!node || !action)
		return (0);

	action(node, depth);

	dep_children = ntt_helper(node->children, action, 1 + depth);
	dep_next = ntt_helper(node->next, action, depth);
	bd = (dep_children > dep_next) ? dep_children : dep_next;

	return (bd);
}

/**
 * nary_tree_traverse - goes through a N-ary tree, node by node
 * @root: root node of the tree
 * @action: function pointer to execute for each node traversed
 *  - node: node being traversed
 *  - depth: depth of the node being traversed
 *
 * Return: biggest depth of the tree pointed to by root
 */
size_t nary_tree_traverse(nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth))
{
	if (!root || !action)
		return (0);

	return (ntt_helper(root, action, 0));
}
