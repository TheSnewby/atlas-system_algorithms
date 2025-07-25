#include "graphs.h"

/**
 * graph_create - creates a graph and initializes content
 *
 * Return: pointer to the new graph or NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *new = NULL;

	new = (graph_t *)malloc(sizeof(graph_t));
	if (!new)
		return (NULL);

	new->nb_vertices = 0;
	new->vertices = NULL;

	return (new);
}
