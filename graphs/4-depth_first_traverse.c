#include "graphs.h"

/**
 * dfs_recursive - performs the recursive dfs function of a graph 
 * @stack: current stack node
 * @depth: current depth
 * @action: function pointer
 * @bvd: biggest vertex depth
 */
void dfs_recursive(vertex_t *vertex, size_t depth, void
	(*action)(const vertex_t *vertex, size_t depth),
	size_t *bvd, size_t *visited)
{
	edge_t *temp_e = NULL;

	if (!vertex || !action || !vertex->edges || visited[vertex->index])
		return;

	visited[vertex->index] = 1;
	action(vertex, depth);

	if (depth > *bvd)
		*bvd = depth;

	temp_e = vertex->edges;
	while (temp_e)
	{
		dfs_recursive(temp_e->dest, 1 + depth, action, bvd, visited);
		temp_e = temp_e->next;
	}
}

/**
 * depth_first_traverse - goes through a graph using the depth-first algorithm
 * @graph: pointer to the graph to traverse. The traversal must start from
 * the first vertex in the vertices list.
 * @action: is a pointer to a function to be called for each visited vertex,
 * its parameters are:
 *  v -> A const pointer to the visited vertex
 *  depth -> The depth of v, from the starting vertex
 * 
 * Note: stack traversal of discovered vertices
 *
 * Return: biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	int i;
	vertex_t *temp_v = NULL;
	edge_t *temp_e = NULL;
	size_t bvd = 0, depth = 0, *visited;

	if (!graph || !action || !graph->vertices || graph->nb_vertices <= 0)
		return (0);

	visited = (size_t *)calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (0);

	/* consider looping through to find disconnected nodes */
	dfs_recursive(graph->vertices, depth, action, &bvd, visited);

	return (bvd);
}
