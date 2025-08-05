#include "huffman.h"

/**
 * huffman_codes_r - recursive printer for codes
 * @root: root of huffman tree
 * @path: path to leaf
 * @index: index of current location in path
 */
static void huffman_codes_r(binary_tree_node_t *root, int *path, int index)
{
	int i;
	symbol_t *root_data = NULL;

	if (!root || !path || index < 0)
		return;

	root_data = (symbol_t *)root->data;
	/* printf("Visiting: %c\n", root_data->data); */

	if (!root->left && !root->right && root_data->data != -1) /* leaf */
	{
		printf("%c: ", root_data->data);
		for (i = 0; i < index; i++)
			printf("%d", path[i]);
		printf("\n");
	}
	if (root->left)
		huffman_codes_r(root->left, path, index + 1);
	if (root->right)
	{
		path[index] = 1;
		huffman_codes_r(root->right, path, index + 1);
	}
}

/**
 * huffman_codes - builds the huffman tree and prints the resulting
 *  huffman codes for each symbol
 * @data: array of data
 * @freq: array of frequencies
 * @size: size of above arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root = NULL;
	int path[10] = {0}, path_i = 0;

	if (!data || !freq || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	huffman_codes_r(root, path, path_i);



	return (1);
}
