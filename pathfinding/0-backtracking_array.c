#include "pathfinding.h"

int check_visited(int x, int y, queue_t *visited);
point_t *create_point(int x, int y);

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
 * populate_unvisited - populates unvisited queue with new options
 * @map: 2D array
 * @visited: queue of visited
 * @x: x coord
 * @y: y coord
 * @rows: number of rows in map
 * @cols: number of cols in map
 *
 * Return: unvisited point_t
 */
point_t *populate_unvisited(char **map,	queue_t *visited,
	int x, int y, int rows, int cols)
{
	point_t *new_point = NULL;

	if (!visited)
		return (NULL);
	printf("Checking coordinates [%d, %d]\n", x, y);
	/* populate new path options */ /* map[y][x] */
	if (x + 1 < cols && map[y][x + 1] == '0' && !check_visited(x + 1, y, visited))
	{
		new_point = create_point(x + 1, y);
		if (!new_point)
			printf("failed new_point RIGHT\n");
	}
	else if (y + 1 < rows && map[y + 1][x] == '0' && !check_visited(x, y + 1, visited))
	{
		new_point = create_point(x, y + 1);
		if (!new_point)
			printf("failed new_point DOWN\n");
	}
	else if (x - 1 >= 0 && map[y][x - 1] == '0' && !check_visited(x - 1, y, visited))
	{
		new_point =  create_point(x - 1, y);
		if (!new_point)
			printf("failed new_point LEFT\n");
	}
	else if (y - 1 >= 0 && map[y - 1][x] == '0' && !check_visited(x, y - 1, visited))
	{
		new_point = create_point(x, y - 1);
		if (!new_point)
			printf("failed new_point UP\n");
	}

	return (new_point);
}

/**
 * check_visited - checks whether the point is in the visited list
 * description: checks most recent first before traversing the rest of the list
 * @x: x coord
 * @y: y coord
 * @visited: queue of visited points
 *
 * Return: 1 if visited, 0 if not visited, -1 on type failure
 */
int check_visited(int x, int y, queue_t *visited)
{
	queue_node_t *temp = NULL;
	point_t *point = NULL, *visited_pt = NULL;

	point = create_point(x, y);
	if (!point || !visited || !visited->front)
		return (-1);

	temp = visited->back;
	while (temp)
	{
		visited_pt = (point_t *)temp->ptr;
		if (POINT_CMP(visited_pt, point))
		{
			free(point);
			return (1);
		}
		temp = temp->prev;
	}
	free(point);

	return (0);
}

/**
 * create_point - creates a point
 * @x: x coord
 * @y: y coord
 *
 * Return: created point, or NULL on failure
 */
point_t *create_point(int x, int y)
{
	point_t *point = NULL;

	if (x < 0 || y < 0)
		return (NULL);

	point = (point_t *)malloc(sizeof(point_t));
	if (!point)
		return (NULL);

	point->x = x;
	point->y = y;

	return (point);
}

/**
 * backtracking_array -  searches for the first path from a starting point to a
 *  target point within a two-dimensional array.
 * @map: 2D array with 0s and 1s representing walkable and blocked cells
 * @rows: numbers of rows in array
 * @cols: number of columns in array
 * @start: starting location in array
 * @target: target location in array
 *
 * Return: queue of path from start to target, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target)
{
	queue_t *visited = NULL, *path = NULL;
	point_t *next_point = NULL, *prev_point = NULL, *start_cpy = NULL,
	*visited_curr_pt_cpy = NULL;
	int x, y;

	if (!map || !start || !target ||
		start->x >= cols || start->y >= rows || POINT_CMP(start, target))
		return (NULL);

	path = queue_create();
	visited = queue_create();
	start_cpy = create_point(start->x, start->y);
	visited_curr_pt_cpy = create_point(start->x, start->y);
	if (!path || !visited || !start_cpy || !visited_curr_pt_cpy)
		return (NULL);

	queue_push_front(visited, (void *)visited_curr_pt_cpy);
	queue_push_front(path, (void *)start_cpy);

	x = start_cpy->x;
	y = start_cpy->y;
	while (path->front)
	{
		next_point = populate_unvisited(map, visited, x, y, rows, cols);
		while (!next_point)
		{
			free(dequeue_back(path));
			if (!path->front)
			{
				queue_delete(visited);
				queue_delete(path);
				return (NULL); /* no valid paths forward */
			}
			prev_point = (point_t *)path->back->ptr;
			x = prev_point->x;
			y = prev_point->y;
			next_point = populate_unvisited(map, visited, x, y, rows, cols);
		}

		x = next_point->x;
		y = next_point->y;

		visited_curr_pt_cpy = create_point(x, y);

		queue_push_back(visited, (void *)visited_curr_pt_cpy);
		queue_push_back(path, (void *)next_point);

		if (POINT_CMP(next_point, target) == 1)
		{
			queue_delete(visited);
			return (path);
		}
	}
	return (NULL);
}
