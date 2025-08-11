#include "pathfinding.h"

int check_visited(int x, int y, queue_t *visited);
point_t *create_point(int x, int y);

/**
 * populate_unvisited - populates unvisited queue with new options
 * @map: 2D array
 * @unvisited: queue of unvisited
 * @visited: queue of visited
 * @x: x coord
 * @y: y coord
 */
static void populate_unvisited(char **map, queue_t *unvisited, queue_t *visited,
	int x, int y, int rows, int cols)
{
	if (!unvisited || !visited)
		return;

	/* populate new path options */
	if (y - 1 >= 0 && !map[x][y - 1] && check_visited(x, y - 1, visited))
		queue_push_front(unvisited, create_point(x, y - 1));
	if (x + 1 >= 0 && !map[x - 1][y] && check_visited(x - 1, y, visited))
		queue_push_front(unvisited, create_point(x - 1, y));
	if (y + 1 < cols && !map[x][y + 1] && check_visited(x, y + 1, visited))
		queue_push_front(unvisited, create_point(x, y + 1));
	if (x + 1 < rows && !map[x + 1][y] && check_visited(x + 1, y, visited))
		queue_push_front(unvisited, create_point(x + 1, y));
}

/**
 * point_cmp - compares points
 * @a: point a
 * @b: point b
 *
 * Return: returns 0 if they match, 1 if they don't, -1 on type failure
 */
int point_cmp(const point_t *a, const point_t *b)
{
	if (!a || !b)
		return (-1);

	if (a->x == b->x && a->y == b->y)
		return (0);
	else
		return (1);
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
	point_t *point = NULL;

	point = create_point(x, y);
	if (!point || !visited || !visited->front)
		return (-1);

	temp = visited->back;
	while (temp)
	{
		if (point_cmp((point_t *)temp->ptr, point) == 0)
			return (1);
		temp = temp->prev;
	}
	free (point);

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
	queue_t *unvisited = NULL, *visited = NULL, *path = NULL;
	point_t *current_point = NULL;
	int x, y;

	if (!map || !start || !target ||
		start->x >= rows || start->y >= cols || start == target)
		return (NULL);

	path = queue_create();
	unvisited = queue_create();
	visited = queue_create();

	if (!path || !unvisited || !visited)
		return (NULL);

	queue_push_front(visited, &start);
	queue_push_front(path, &start);

	x = start->x;
	y = start->y;
	do
	{
		populate_unvisited(map, unvisited, visited, x, y, rows, cols);
		current_point = dequeue(unvisited);
		while (!current_point)
		{
			current_point = dequeue(visited);
			dequeue(path);
			if (!visited->front)
				return (NULL); /* no valid paths forward */
		}

		queue_push_front(visited, &current_point);
		queue_push_back(path, &current_point);

		if (point_cmp(current_point, target) == 0)
		{
			queue_delete(unvisited);
			queue_delete(visited);
			return (path);
		}

	} while (unvisited->front);

	return (NULL);
}
