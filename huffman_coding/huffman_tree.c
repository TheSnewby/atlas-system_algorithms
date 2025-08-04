#include "huffman.h"

/**
 * huffman_tree - builds a Huffman tree
 * @data: array of data
 * @freq: array of frequencies
 * @size: size of above arrays
 *
 * Return: root node of created Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *prio_queue = NULL;
	binary_tree_node_t *huffman_root = NULL;

	if (!data || !freq || size == 0)
		return (NULL);

	prio_queue = huffman_priority_queue(data, freq, size);
	if (!prio_queue)
		return (NULL);

	while (prio_queue->size > 1)
		huffman_extract_and_insert(prio_queue);

	huffman_root = heap_extract(prio_queue);

	free(prio_queue);

	return (huffman_root);
}
