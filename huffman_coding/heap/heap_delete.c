#include "heap.h"

/**
 * heap_delete_rec - recursive helper for heap_delete
 * @root: root node
 * @free_data: pointer to function to free data
 */
void heap_delete_rec(binary_tree_node_t *root, void (*free_data)(void *))
{
	if (!root)
		return;

	if (root->left)
		heap_delete_rec(root->left, free_data);
	if (root->right)
		heap_delete_rec(root->right, free_data);

	if (free_data)
		free_data(root->data);
	free(root);
	root = NULL;
}

/**
 * heap_delete - deallocates a heap
 * @heap: heap to be deallocated
 * @free_data: function to handle data
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	heap_delete_rec(heap->root, free_data);
	free(heap);
	heap = NULL;
}
