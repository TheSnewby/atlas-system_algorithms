#include "nary_trees.h"

/**
 * path_exists - checks that a path exists in an N-ary tree
 * @root: root of tree
 * @path: path to root
 *
 * Return: return 1 if all the elements of path are present in the tree
 * and if for an element of path at the index i is present in one of the nodes
 * at the depth i. And of course, all the nodes must be linked to form a path.
 * 0 otherwise
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	int i = 0, not_found = 0;
	nary_tree_t const *temp = NULL;

	if (!root || !path)
		return (0);
	temp = root;
	if (strcmp(temp->content, path[i]) == 0)
	{
		i++;
		temp = temp->children;
	}
	else
		return (0);
	while (temp && path[i] && !not_found)
	{
		if (strcmp(temp->content, path[i]) == 0) /* check child */
		{
			i++;
			temp = temp->children;
		}
		else /* check siblings */
		{
			temp = temp->next;
			while (temp)
			{
				if (strcmp(temp->content, path[i]) == 0)
				{
					i++;
					temp = temp->children;
					break;
				}
				temp = temp->next;
			}
		}
		if (!temp && path[i])
			not_found++;
	}
	if (not_found)
		return (0);
	return (1);
}
