#include "graphs.h"

/**
 * breath_first_traverse - goes through a graph using the depth-first algorithm
 * @graph: pointer to the graph to traverse. The traversal must start from
 * the first vertex in the vertices list.
 * @action: is a pointer to a function to be called for each visited vertex,
 * its parameters are:
 *  v -> A const pointer to the visited vertex
 *  depth -> The depth of v, from the starting vertex
 *
 * Return: biggest vertex depth, or 0 on failure
 */
size_t breath_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	/* queue traversal of discovered vertices */
	/* queue being a singly ll where nodes are placed at end and popped from head */

	
}
