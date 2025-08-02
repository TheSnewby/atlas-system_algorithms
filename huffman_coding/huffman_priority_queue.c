#include "huffman.h"

/**
 * data_cmp - compares data between nodes' symbols
 * @p1: first pointer
 * @p2: second pointer
 *
 * Return: Difference between the two frequencies
 */
int data_cmp(void *p1, void *p2)
{
	symbol_t *s1, *s2;
	int n1, n2;

	s1 = (symbol_t *)p1;
	s2 = (symbol_t *)p2;
	n1 = (int)s1->freq;
	n2 = (int)s2->freq;

	return (n1 - n2);
}

/**
 * huffman_priority_queue - creates a priority queue for huffman algorithm
 * @data: array of characters of size size
 * @freq: array of associated frequencies of size size
 * @size: size of arrays
 *
 * Return: priority queue or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	size_t i;
	heap_t *queue = NULL;
	symbol_t *sym = NULL;
	binary_tree_node_t *node = NULL;

	if (!data || !freq || !size)
		return (NULL);

	queue = heap_create(data_cmp);
	if (!queue)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		sym = symbol_create(data[i], freq[i]);
		if (!sym)
			return (NULL);

		node = binary_tree_node(NULL, sym);
		if (!node)
			return (NULL);

		if (!heap_insert(queue, node))
			return (NULL);
	}
	return (queue);
}
