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
 * heap_extract - extracts the root data
 * @heap: heap
 *
 * Return: data or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *data = NULL;
	size_t bitwise_pos = 0;
	binary_tree_node_t *temp = NULL;

	if (!heap || !heap->root || heap->size == 0)
		return (NULL);

	data = heap->root->data;
	temp = heap->root;

	while ((1U << (bitwise_pos + 1)) <= heap->size)
		bitwise_pos++;

	bitwise_pos--;
	while (bitwise_pos > 0)
	{
		if (heap->size & (1U << bitwise_pos))
			temp = temp->right;
		else
			temp = temp->left;
		bitwise_pos--;
	}

	heap->root->data = temp->data;

	if (temp->parent->left == temp)
		temp->parent->left = NULL;
	else
		temp->parent->right = NULL;
	free(temp);

	heap->size--;

	temp = heap->root;

	while (temp)
	{
		if (temp->left && temp->right)
		{
			if (temp->left->data < temp->right->data && temp->data > temp->left->data)
			{
				swap_data(temp, temp->left);
				temp = temp->left;
			}
			else if (temp->left->data > temp->right->data && temp->data > temp->right->data)
			{
				swap_data(temp, temp->right);
				temp = temp->right;
			}
			else
				break;
		}
		else if (temp->left && temp->data > temp->left->data)
		{
			swap_data(temp, temp->left);
			temp = temp->left;
		}
		else if (temp->right && temp->data > temp->right->data)
		{
			swap_data(temp, temp->right);
			temp = temp->right;
		}
		else
			break;
	}
	/** Once the data is extracted,
	 * the root node must be freed, (i just swapped data)
	 * and replaced by the last node of the heap.
	 * Then the heap must be rebuilt if necessary
	 */

	return (data);
}
