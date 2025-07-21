#include "graphs.h"
/**
 * create_new_edge - creates a new edge
 * @dest_ver: is the the vertex to connect to
 *
 * Return: pointer to new edge, NULL if failure
 */
edge_t *create_new_edge(vertex_t *dest_ver)
{
	edge_t *new_edge = NULL;

	new_edge = (edge_t *)malloc(sizeof(edge_t));

	if (!new_edge)
		return (NULL);
	new_edge->dest = dest_ver;
	new_edge->next = NULL;

	return (new_edge);
}

/**
 * graph_add_edge - adds an edge between two vertices
 * @graph: is a pointer to the graph to add the edge to
 * @src: is the string identifying the vertex to make the connection from
 * @dest: is the string identifying the vertex to connect to
 * @type: is the type of edge
 * UNIDIRECTIONAL: Only one edge is created connecting src to dest
 * BIDIRECTIONAL: Two edges are created, connecting src to dest
 *  AND dest to src.
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
	edge_type_t type)
{
	vertex_t *src_ver = NULL, *dest_ver = NULL, *temp_vert;
	edge_t *new_edge = NULL, *temp_edge;

	if (!graph || !src || !dest || (strcmp(src, dest) == 0))
		return (0);
	temp_vert = graph->vertices;
	while (temp_vert)
	{
		if (strcmp(temp_vert->content, src) == 0)
			src_ver = temp_vert;
		if (strcmp(temp_vert->content, dest) == 0)
			dest_ver = temp_vert;
		temp_vert = temp_vert->next;
	}
	if (!src_ver || !dest_ver)
		return (0);
	new_edge = create_new_edge(dest_ver);
	if (!src_ver->edges)
		src_ver->edges = new_edge;
	else
	{
		temp_edge = src_ver->edges;
		while (temp_edge->next)
			temp_edge = temp_edge->next;
		temp_edge->next = new_edge;
	}
	if (type == BIDIRECTIONAL)
	{
		new_edge = create_new_edge(src_ver);
		if (!dest_ver->edges)
			dest_ver->edges = new_edge;
		else
		{
			temp_edge = dest_ver->edges;
			while (temp_edge->next)
				temp_edge = temp_edge->next;
			temp_edge->next = new_edge;
		}
	}
	return (1);
}
