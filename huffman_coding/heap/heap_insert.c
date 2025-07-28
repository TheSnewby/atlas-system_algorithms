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
 * heap_insert_recurse - performs recursive function of min heap insert
 * @heap: heap
 * @node: current node
 * @data: data
 *
 * Return: new node containing data or NULL on failure
 */
binary_tree_node_t *heap_insert_recurse(heap_t *heap,
	binary_tree_node_t *node, void *data)
{
	binary_tree_node_t *new_node = NULL;

	if (!heap->root)
	{
		new_node = binary_tree_node(NULL, data);
		heap->size++;
		heap->root = new_node;
		return (new_node);
	}
	else if (!node->left)
	{
		new_node = binary_tree_node(node, data);
		node->left = new_node;
		if (heap->data_cmp(node->data, new_node->data) > 0) /* n1 - n2 */
			swap_data(node, new_node);
		heap->size++;
		return (new_node);
	}
	else if (!node->right)
	{
		new_node = binary_tree_node(node, data);
		node->right = new_node;
		if (heap->data_cmp(node->data, new_node->data) > 0) /* n1 - n2 */
			swap_data(node, new_node);
		heap->size++;
		return (new_node);
	}

	new_node = heap_insert_recurse(heap, node->left, data);
	if (!new_node)
		new_node = heap_insert_recurse(heap, node->right, data);

	if (new_node && heap->data_cmp(node->data, new_node->data) > 0) /* n1 - n2 */
		swap_data(node, new_node);

	return (new_node);
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
	binary_tree_node_t *new_node = NULL;

	if (!heap || !data)
		return (NULL);  /* or create new heap, but don't know data_cmp */

	new_node = heap_insert_recurse(heap, heap->root, data);

	return (new_node);
}
