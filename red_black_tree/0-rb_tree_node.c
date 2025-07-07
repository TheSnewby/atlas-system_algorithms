#include "rb_trees.h"

/**
 * rb_tree_node - creates a red-black tree node
 * @parent: parent node
 * @value: value
 * @color: color of the node
 *
 * Return: created node or NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node;

	if (!parent || (color != BLACK && color != RED && color != DOUBLE_BLACK))
		return (NULL);

	node = (rb_tree_t *)malloc(sizeof(rb_tree_t));
	if (!node)
		return (NULL);

	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->n = value;
	node->color = color;

	return (node);
}
