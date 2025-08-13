#ifndef pathfinding_h
#define pathfinding_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphs.h"
#include "queues.h"

#define POINT_CMP(a, b) (!(a) || !(b) ? -1 : \
((a)->x == (b)->x && (a)->y == (b)->y) ? 1 : 0)
#define VERTEX_CMP(a, b) (!(a) || !(b) ? -1 : \
(strcmp(a->content, b->content) == 0) ? 1 : 0)

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target);
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target);

#endif
