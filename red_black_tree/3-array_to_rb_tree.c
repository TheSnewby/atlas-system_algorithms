#include "rb_trees.h"

/**
 * array_to_rb_tree - array of values to red-black tree
 * @array: array of values
 * @size: size of array
 *
 * Return: red-black tree
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	size_t i;
	rb_tree_t *rbtree = NULL;

	if (!array || size < 1)
		return (NULL);

	for (i = 0; i < size; i++)
		rbtree = rb_tree_insert(NULL, array[i]);

	return (rbtree);
}
