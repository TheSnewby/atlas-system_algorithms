#include "heap.h"

/**
 * heap_create - creates a new heap
 * @data_cmp: the function to compare two nodes
 *
 * Return: pointer to new heap, or NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap = NULL;

	if (!data_cmp)
		return (NULL);

	heap = (heap_t *)malloc(sizeof(heap_t));
	if (!heap)
		return (NULL);

	heap->data_cmp = data_cmp;
	heap->root = NULL;
	heap->size = 0;

	return (heap);
}
