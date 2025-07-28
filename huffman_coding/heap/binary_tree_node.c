#include "heap.h"

/**
 * binary_tree_node - creates a generic binary tree node
 * @parent: pointer to parent
 * @data: data for node
 *
 * Return: new node or NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node = NULL;

	if (!data)
		return (NULL);

	node = (binary_tree_node_t *)malloc(sizeof(binary_tree_node_t));
	if (!node)
		return (NULL);

	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;

	return (node);
}
