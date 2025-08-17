#include "nary_trees.h"

/**
 * nary_tree_insert - inserts a node in a N-ary tree
 * @parent: pointer to the parent node
 * @str: str to be stored in the created node - must be duplicated
 *
 * Return: pointer to created node, or NULL on failure
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node = NULL;
	char *content = NULL;

	if (!str)
		return (NULL);

	content = strdup(str);
	if (!content)
		return (NULL);

	new_node = (nary_tree_t *)malloc(sizeof(nary_tree_t));
	if (!new_node)
		return (NULL);

	new_node->children = NULL;
	new_node->content = content;
	new_node->nb_children = 0;
	new_node->next = NULL;

	if (!parent)
		new_node->parent = NULL;
	else
	{
		new_node->parent = parent;
		if (parent->children)
			new_node->next = parent->children;
		parent->nb_children++;
		parent->children = new_node;
	}

	return (new_node);
}
