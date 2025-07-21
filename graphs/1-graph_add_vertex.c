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
	vertex_t *new_vertex = NULL, *temp;

	if (!graph || !str)
		return (NULL);

	temp = graph->vertices;
	while (temp)
	{
		if (strcmp(temp->content, str) == 0)
			return (NULL);
		temp = temp->next;
	}

	new_vertex = (vertex_t *)malloc(sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	new_vertex->index = graph->nb_vertices++;
	new_vertex->content = strdup(str);
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (!graph->vertices)
		graph->vertices = new_vertex;
	else
	{
		temp = graph->vertices;
		while (temp->next)
			temp = temp->next;
		temp->next = new_vertex;
	}

	return (new_vertex);
}
