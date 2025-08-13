#include "pathfinding.h"

/**
 * free_path - Unstacks the queue to discover the path from the starting
 * vertex to the target vertex. Also deallocates the queue.
 *
 * @path: Queue containing the path
 */
static void free_path(queue_t *path)
{
	char *city = NULL;

	while (path->front)
	{
		city = (char *)dequeue(path);
		free(city);
	}
	free(path);
}

/**
 * dequeue_back - Pops out the back node of a queue
 * @queue: Pointer to the queue
 *
 * Return: A pointer to the data of the popped node, NULL on failure
 */
void *dequeue_back(queue_t *queue)
{
	queue_node_t *tmp;
	void *ptr;

	if (!queue || !queue->back)
		return (NULL);

	ptr = queue->back->ptr;
	tmp = queue->back;

	if (queue->back->prev)
		queue->back->prev->next = NULL;
	else
		queue->front = NULL;

	queue->back = queue->back->prev;
	free(tmp);
	tmp = NULL;
	return (ptr);
}

/**
 * backtracking_graph_r - recursive backtracking search for target
 * @current: current vertex
 * @visited: array of vertex indices where 0 is unvisited, and 1 is visited
 * @path: path from start to target
 * @target: target vertex
 *
 * Return: 1 when found, 0 when backtracking
 */
int backtracking_graph_r(const vertex_t *current, size_t *visited,
	queue_t *path, vertex_t const *target)
{
	edge_t *next_e = NULL;

	if (!visited[current->index])
		printf("Checking %s\n", current->content);

	visited[current->index] = 1;
	queue_push_back(path, strdup(current->content));

	if (VERTEX_CMP(current, target))
		return (1);

	next_e = current->edges;
	while (next_e)
	{
		if (!visited[next_e->dest->index])
			if (backtracking_graph_r(next_e->dest, visited, path, target))
				return (1);
		next_e = next_e->next;
	}
	if (path->back)
		free(dequeue_back(path));
	return (0);
}

/**
 * backtracking_graph - searches for the first path from a starting point
 *  to a target point in a graph
 * @graph: the graph
 * @start: starting vertex
 * @target: target vertex
 *
 * Return: path from start to finish, or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph,
	vertex_t const *start, vertex_t const *target)
{
	queue_t *path = NULL;
	size_t *visited = NULL;

	if (!graph || !start || !target || VERTEX_CMP(start, target))
		return (NULL);

	visited = (size_t *)calloc(graph->nb_vertices, sizeof(size_t));
	path = queue_create();
	if (!visited || !path)
		return (NULL);

	if (backtracking_graph_r(start, visited, path, target))
	{
		free(visited);
		return (path);
	}

	free(visited);
	free_path(path);
	return (NULL);
}
