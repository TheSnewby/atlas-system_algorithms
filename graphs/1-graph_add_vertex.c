#include "graphs.h"

/**
 * graph_add_vertex - adds a vertex to an existing graph
 * @graph: graph
 * @str: content of new vertex
 *
 * Return: new vertex
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex = NULL;

	new_vertex = (vertex_t *)malloc(sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	new_vertex->index = 0;
	strcpy(new_vertex->content, str);
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	graph->vertices = 0;
	graph->nb_vertices++;

	return (new_vertex);
}
