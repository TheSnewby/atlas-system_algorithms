#include "graphs.h"

/**
 * vertex_list_check - checks whether vertex in stack
 * @list: list of discovered vertices
 * @vertex: vertex to check
 *
 * Return: 1 if in, 0 if not, -1 if failure
 */
int vertex_list_check(stack_t *list, vertex_t *vertex)
{
	stack_t *temp = 0;

	if (!list || !vertex)
		return (0);

	temp = list->vertex;
	while (temp)
	{
		if (temp->vertex == vertex)
			return (1);
	}

	return (0);
}

/**
 * create_stack - creates a stack
 * @vertex: first vertex
 *
 * Return: new stack, or NULL on failure
 */
stack_t *create_stack(vertex_t *vertex)
{
	stack_t *new = NULL;

	new = (stack_t *)malloc(sizeof(stack_t));
	if (!new)
		return (NULL);

	new->vertex = vertex;
	new->next = NULL;

	return (new);
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
 * Return: biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	/* stack traversal of discovered vertices */
	/* stack being a singly ll where nodes are placed and popped from head */
	vertex_t *temp_v = NULL;
	edge_t *temp_e = NULL;
	size_t bvd = 0;
	stack_t *stack, *list, *temp_s, *temp_list_s;

	if (!graph || !action)
		return (0);

	temp_v = graph->vertices;


	stack = create_stack(temp_v);
	list = create_stack(temp_v);
	temp_s = create_stack(NULL); /* necessary? */
	if (!stack || !list || !temp_s)
		return (0);

	while (stack->vertex)
	{
		temp_v = stack->vertex; /* pop from stack*/
		stack = stack->next; 

		temp_e = temp_v->edges;
		while (temp_e)
		{
			if (vertex_list_check(list, temp_e->dest) == 0)
			{
				if (!stack)
					stack = temp_e->dest;
				else
				{
					temp_s->vertex = temp_e->dest;
					temp_s->next = stack;
					stack = temp_s;
				}
				temp_list_s = list;
				/* add vertex to "list" */
			}
			temp_e = temp_e->next;
		}
		action(temp_v, bvd); /* what do i do with bvd? */
	}
	free(stack);
	free(list);
	free(temp_s);

	return (bvd);
}
