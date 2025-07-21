#include "graphs.h"

/**
 * graph_delete - deletes a graph
 * @graph: graph to be deleted
 */
void graph_delete(graph_t *graph)
{
	vertex_t *tmp_v = NULL, *del_v;
	edge_t *tmp_e = NULL, *del_e;

	if (!graph)
		return;

	tmp_v = graph->vertices;
	while (tmp_v)
	{
		tmp_e = tmp_v->edges;
		while (tmp_e)
		{
			del_e = tmp_e;
			tmp_e = tmp_e->next;
			free(del_e); /* frees edge */
		}

		del_v = tmp_v;
		tmp_v = tmp_v->next;
		free(del_v->content); /* frees content */
		free(del_v); /* frees vertex */
	}
	free(graph); /* frees graph */
}
