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
 * heapify_down - moves a value from the top downwards in a min heap
 * @heap: heap
 */
void heapify_down(heap_t *heap)
{
	binary_tree_node_t *temp = NULL;

	if (!heap)
		return;

	temp = heap->root;

	while (temp)
	{
		if (temp->left && temp->right)
		{
			if (heap->data_cmp(temp->left->data, temp->right->data) < 0 &&
			heap->data_cmp(temp->data, temp->left->data) > 0)
			{
				swap_data(temp, temp->left);
				temp = temp->left;
			}
			else if (heap->data_cmp(temp->left->data, temp->right->data) > 0 &&
			heap->data_cmp(temp->data, temp->right->data) > 0)
			{
				swap_data(temp, temp->right);
				temp = temp->right;
			}
			else
				break;
		}
		else if (temp->left && heap->data_cmp(temp->data, temp->left->data) > 0)
		{
			swap_data(temp, temp->left);
			temp = temp->left;
		}
		else if (temp->right && heap->data_cmp(temp->data, temp->right->data) > 0)
		{
			swap_data(temp, temp->right);
			temp = temp->right;
		}
		else
			break;
	}
}

/**
 * last_node - finds last node in a heap
 * @heap: heap
 *
 * Return: last node, or NULL if not found
 */
binary_tree_node_t *last_node(heap_t *heap)
{
	binary_tree_node_t *temp = NULL;
	size_t path_mask = 1, i;

	if (!heap || !heap->root || heap->size <= 0)
		return (NULL);

	if (heap->size == 1)
		return (heap->root);

	/* finds level of path to last node after root */
	while ((path_mask << 1) <= heap->size)
		path_mask <<= 1;

	/* drive to last node */
	temp = heap->root;
	for (i = path_mask >> 1; i > 0; i >>= 1)
	{
		if (heap->size & i)
			temp = temp->right;
		else
			temp = temp->left;
	}
	return (temp);
}

/**
 * heap_extract - extracts the root data
 * @heap: heap
 *
 * Return: data or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *data = NULL;
	binary_tree_node_t *last = NULL;

	if (!heap || !heap->root || heap->size == 0)
		return (NULL);

	data = heap->root->data;

	last = last_node(heap);
	if (!last)
		return (NULL);
	if (last == heap->root)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size--;
		return (data);
	}

	heap->root->data = last->data;
	/* parent cleanup */
	if (last->parent && last->parent->left && last->parent->left == last)
		last->parent->left = NULL;
	else if (last->parent && last->parent->right && last->parent->right == last)
		last->parent->right = NULL;

	/* free and downsize */
	free(last);
	last = NULL;
	heap->size--;

	heapify_down(heap);

	return (data);
}
