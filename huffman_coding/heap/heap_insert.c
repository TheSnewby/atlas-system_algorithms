#include "heap.h"

/**
 * swap_data - swaps data between two nodes
 * @parent: parent node
 * @new_node: current node
 */
static void swap_data(binary_tree_node_t *parent, binary_tree_node_t *new_node)
{
	void *temp_data;

	temp_data = parent->data;
	parent->data = new_node->data;
	new_node->data = temp_data;
}

/**
 * parent_finder - returns the parent node of the location of the new node
 * @heap: heap
 * @i: index of new location
 *
 * Return: pointer to parent
 */
binary_tree_node_t *parent_finder(heap_t *heap, size_t i)
{
	size_t parent_i, depth = 0, path[16], temp_i;
	binary_tree_node_t *parent = NULL;

	if (!i)
		return (NULL);

	parent_i = (i - 1) / 2;

	temp_i = parent_i;
	while (temp_i > 0)
	{
		path[depth] = temp_i % 2;
		depth++;
		temp_i = (temp_i - 1) / 2;
	}

	parent = heap->root;
	for (i = depth; i > 0; i--)
	{
		if (path[i - 1])
			parent = parent->left;
		else
			parent = parent->right;
	}

	return (parent);
}

/**
 * heap_insert - inserts a node into a heap with specific data
 * @heap: heap
 * @data: data
 *
 * Return: new node containing data or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node = NULL, *parent = NULL;

	if (!heap || !data)
		return (NULL);  /* or create new heap, but don't know data_cmp */

	if (!heap->root)
	{
		new_node = binary_tree_node(NULL, data);
		if (!new_node)
			return (NULL);
		heap->root = new_node;
		heap->size = 1;
		return (new_node);
	}

	parent = parent_finder(heap, heap->size);
	if (!parent)
		return (NULL);

	new_node = binary_tree_node(parent, data);
	if (!new_node)
		return (NULL);

	if (heap->size & 1)
		parent->left = new_node;
	else
		parent->right = new_node;
	heap->size++;

	while (new_node->parent &&
		heap->data_cmp(new_node->data, new_node->parent->data) < 0)
	{
		swap_data(new_node, new_node->parent);
		new_node = new_node->parent;
	}

	return (new_node);
}
