#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two nodes of the prio queue
 *  and inserts a new one
 * @priority_queue: the prio queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	symbol_t *new_sym = NULL, *left_sym = NULL, *right_sym = NULL;
	binary_tree_node_t *new_node = NULL, *left = NULL, *right = NULL;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	left = heap_extract(priority_queue);
	if (!left)
		return (0);
	right = heap_extract(priority_queue);
	if (!right)
		return (0);

	left_sym = (symbol_t *)left->data;
	right_sym = (symbol_t *)right->data;

	new_sym = symbol_create(-1, left_sym->freq + right_sym->freq);
	new_node = binary_tree_node(NULL, new_sym);
	if (!new_node)
		return (0);
	new_node->left = left;
	new_node->right = right;

	if (!heap_insert(priority_queue, new_node))
		return (0);

	return (1);
}
