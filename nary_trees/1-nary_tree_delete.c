#include "nary_trees.h"

/**
 * nary_tree_delete - deletes an entire N-ary tree
 * @tree: N-ary tree to be deleted
 */
void nary_tree_delete(nary_tree_t *tree)
{
	if (!tree)
		return;

	if (tree->children)
		nary_tree_delete(tree->children);
	if (tree->next)
		nary_tree_delete(tree->next);
	/* should parent be handled if given not at the top of the tree? */
	/* if so, make it the first call? */
	free(tree->content);
	free(tree);
}
