#include "pathfinding.h"

/**
 * min_distance - populate list of min distances between start and each vertex
 * @dist: array of distancs
 * @visited: array of visited indices
 * @nb_vertices: number of vertices
 *
 * Return: current minimum index
 */
size_t min_distance(size_t *dist, size_t *visited, size_t nb_vertices)
{
	size_t min = SIZE_MAX, min_index = SIZE_MAX, i;

	for (i = 0; i < nb_vertices; i++)
	{
		if (!visited[i] && dist[i] <= min)
		{
			min = dist[i];
			min_index = i;
		}
	}
	return (min_index);
}

/**
 * construct_path - constructs path queue from prev array
 * @graph: graph
 * @prev: array of previous indices
 * @target_i: target index
 *
 * Return: path, or NULL on failure
 */
queue_t *construct_path(graph_t *graph, int *prev, size_t target_i)
{
	queue_t *path = NULL;
	size_t temp_stack[1024] = {0}, i = target_i;
	vertex_t *temp_v = NULL;
	int top = -1;

	if (!graph || !prev)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	while (1)
	{
		if (i >= graph->nb_vertices)
		{
			queue_delete(path);
			return (NULL);
		}
		temp_stack[++top] = i;
		if (prev[i] == -1)
			break;
		i = prev[i];
	}

	while (top >= 0)
	{
		temp_v = graph->vertices;
		while (temp_v && temp_v->index != temp_stack[top])
			temp_v = temp_v->next;

		if (temp_v)
			queue_push_back(path, strdup(temp_v->content));
		top--;
	}
	return (path);
}

/**
 * dijkstra_graph - searches for the shortest path from a starting point
 *  to a target point in a graph
 * @graph: graph
 * @start: starting vertex
 * @target: target vertex
 *
 * Return: shortest path, or NULL on failure
 */
queue_t *dijkstra_graph(graph_t *graph,
	vertex_t const *start, vertex_t const *target)
{
	size_t *distance = NULL, *visited = NULL, i, min_i;
	edge_t *temp_e = NULL;
	queue_t *path = NULL;
	vertex_t *min_v = NULL;
	int *prev = NULL;

	if (!graph || !graph->vertices || !start || !target)
		return (NULL);

	distance = (size_t *)calloc(graph->nb_vertices, sizeof(size_t));
	visited = (size_t *)calloc(graph->nb_vertices, sizeof(size_t));
	prev = (int *)malloc(graph->nb_vertices * sizeof(int));
	if (!distance || !visited || !prev)
		return (NULL);

	for (i = 0; i < graph->nb_vertices; i++)
	{
		distance[i] = SIZE_MAX;
		prev[i] = -1;
	}

	distance[start->index] = 0;

	while (1)
	{
		min_i = min_distance(distance, visited, graph->nb_vertices);
		if (min_i == SIZE_MAX)
			break; // no more reachable vertices

		if (distance[min_i] == SIZE_MAX)
			break; // vertex is unreachable, stop processing

		visited[min_i] = 1;

		min_v = graph->vertices;
		while (min_v && min_v->index != min_i)
			min_v = min_v->next;

		if (min_v)
			printf("Checking %s, distance from %s is %zu\n",
				min_v->content, start->content, distance[min_i]);

		if (min_i == target->index)
			break;

		for (temp_e = min_v->edges; temp_e; temp_e = temp_e->next)
		{
			if (!visited[temp_e->dest->index] &&
				distance[min_i] + temp_e->weight < distance[temp_e->dest->index])
			{
				distance[temp_e->dest->index] = distance[min_i] + temp_e->weight;
				prev[temp_e->dest->index] = min_i;
			}
		}
	}
	if (distance[target->index] != SIZE_MAX)
		path = construct_path(graph, prev, target->index);
	free(distance);
	free(visited);
	free(prev);
	return (path);
}
