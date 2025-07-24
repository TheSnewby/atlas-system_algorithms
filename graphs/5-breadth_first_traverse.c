#include "graphs.h"

/**
 * dequeue - dequeues a vertex
 * @queue: queue
 *
 * Return: vertex at head
 */
vertex_t *dequeue(queue_t *queue)
{
	vertex_t *vertex;
	queue_node_t *node;

	if (!queue || !queue->head)
		return (NULL);

	node = queue->head;
	vertex = node->vertex;
	queue->head = queue->head->next;

	if (!queue->head)
		queue->tail = NULL;

	free(node);

	return (vertex);
}

/**
 * enqueue - enqueue a vertex
 * @queue: current queue
 * @depth: depth
 * @vertex: vertex
 *
 * Return: head of queue
 */
queue_t *enqueue(queue_t *queue, vertex_t *vertex, size_t depth)
{
	queue_node_t *new_node = NULL;

	new_node = (queue_node_t *)malloc(sizeof(queue_node_t));
	if (!new_node)
		return (NULL);

	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = NULL;

	if (!queue->head)
	{
		queue->head = new_node;
		queue->tail = new_node;
	}
	else
	{
		queue->tail->next = new_node;
		queue->tail = new_node;
	}

	return (queue);
}

/**
 * create_queue - creates a queue
 *
 * Return: newly created queue
 */
queue_t *create_queue()
{
	queue_t *queue = NULL;

	queue = (queue_t *)malloc(sizeof(queue_t));
	if (!queue)
		return (NULL);

	queue->head = NULL;
	queue->tail = NULL;

	return (queue);
}

/**
 * breadth_first_traverse - goes through a graph using the BFS algorithm
 * @graph: pointer to the graph to traverse. The traversal must start from
 * the first vertex in the vertices list.
 * @action: is a pointer to a function to be called for each visited vertex,
 * its parameters are:
 *  v -> A const pointer to the visited vertex
 *  depth -> The depth of v, from the starting vertex
 *
 * Return: biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	/* queue traversal of discovered vertices */
	/* enqueue at tail and dequeue from head */
	vertex_t *temp_v = NULL;
	edge_t *temp_e = NULL;
	queue_t *queue = NULL;
	size_t depth = 0, bvd = 0, *visited;

	if (!graph || !action || !graph->vertices || graph->nb_vertices <= 0)
		return (0);

	visited = (size_t *)calloc(graph->nb_vertices, sizeof(size_t));
	if (!visited)
		return (0);

	queue = create_queue();
	enqueue(queue, graph->vertices, 0);

	while (queue && queue->head)
	{
		depth = queue->head->depth; /* handle depth and bvd */
		if (depth > bvd)
			bvd = depth;
		temp_v = dequeue(queue);

		if (visited[temp_v->index])
			continue;

		action(temp_v, depth);
		visited[temp_v->index] = 1;
		temp_e = temp_v->edges;


		while (temp_e) /* enqueue all edges */
		{
			enqueue(queue, temp_e->dest, 1 + depth);
			temp_e = temp_e->next;
		}
	}
	free(queue);
	return (bvd);
}
