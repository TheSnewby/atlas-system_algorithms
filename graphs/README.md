# Graphs

This repository contains implementations of various graph data structures and algorithms in C, as part of the `atlas-system_algorithms` project.

## Learning Objectives

By the end of this project, you should be able to explain the following concepts without external help:

*   What is a graph?
*   What are vertices and edges?
*   What are the different types of graphs (directed, weighted, etc.)?
*   What are the most common ways to represent graphs in C?
*   How to traverse a graph using Depth-First Search (DFS) and Breadth-First Search (BFS)?

## General Requirements

*   Allowed editors: `vi`, `vim`, `emacs`
*   All files will be compiled on Ubuntu 20.04 LTS.
*   C programs and functions will be compiled with `gcc 9.4.0` using the flags `-Wall -Werror -Wextra -pedantic`.
*   All files must end with a new line.
*   A `README.md` file at the root of the project folder is mandatory.
*   Code must adhere to the Betty style. It will be checked using `betty-style.pl` and `betty-doc.pl`.
*   Global variables are not allowed.
*   No more than 5 functions per file.
*   The standard library is allowed.
*   `main.c` files provided in the examples are for testing purposes only and should not be pushed to the repository. Our own `main.c` files will be used for compilation.
*   Function prototypes for all functions must be included in the `graphs.h` header file.
*   The `graphs.h` header file must be pushed to the repository.
*   All header files must be include-guarded.

## Data Structures

The following data structures and types are used for graph representation and are defined in `graphs.h`:

```c
/**
 * enum edge_type_e - Enumerates the different types of
 * connection between two vertices
 *
 * @UNIDIRECTIONAL: The connection is made only in one way
 * @BIDIRECTIONAL: The connection is made in two ways
 */
typedef enum edge_type_e
{
    UNIDIRECTIONAL = 0,
    BIDIRECTIONAL
} edge_type_t;

/* Define the structure temporarily for usage in the edge_t */
typedef struct vertex_s vertex_t;

/**
 * struct edge_s - Node in the linked list of edges for a given vertex
 * A single vertex can have many edges
 *
 * @dest: Pointer to the connected vertex
 * @next: Pointer to the next edge
 */
typedef struct edge_s
{
    vertex_t    *dest;
    struct edge_s   *next;
} edge_t;


/**
 * struct vertex_s - Node in the linked list of vertices in the adjacency list
 *
 * @index: Index of the vertex in the adjacency list.
 * @content: Custom data stored in the vertex (here, a string)
 * @nb_edges: Number of conenctions with other vertices in the graph
 * @edges: Pointer to the head node of the linked list of edges
 * @next: Pointer to the next vertex in the adjacency linked list
 *   This pointer points to another vertex in the graph, but it
 *   doesn't stand for an edge between the two vertices
 */
struct vertex_s
{
    size_t      index;
    char        *content;
    size_t      nb_edges;
    edge_t      *edges;
    struct vertex_s *next;
};

/**
 * struct graph_s - Representation of a graph
 * We use an adjacency linked list to represent our graph
 *
 * @nb_vertices: Number of vertices in our graph
 * @vertices: Pointer to the head node of our adjacency linked list
 */
typedef struct graph_s
{
    size_t      nb_vertices;
    vertex_t    *vertices;
} graph_t;
```

## Tasks

### 0. Create graph

`0-graph_create.c`

This function allocates memory for a `graph_t` structure and initializes its content.

```c
graph_t *graph_create(void);
```

**Return:** A pointer to the allocated `graph_t` structure, or `NULL` on failure.

**Example Usage:**

```c
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    printf("Successfully created graph\n");

    return (EXIT_SUCCESS);
}
```

### 1. Add a vertex

`1-graph_add_vertex.c`

This function adds a new vertex to an existing graph.

```c
vertex_t *graph_add_vertex(graph_t *graph, const char *str);
```

*   `graph`: A pointer to the graph to add the vertex to.
*   `str`: The string to store in the new vertex.

**Return:** A pointer to the created `vertex_t`, or `NULL` on failure.

**Notes:**
*   The vertex must store a copy of the string `str`.
*   If a vertex with the same string `str` already exists in the graph, the function must fail and ensure no memory leaks.

**Example Usage:**

```c
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

// Assuming graph_create and graph_display are available
// For testing purposes, you might include their implementations or link against them.

int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    if (!graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    if (!graph_add_vertex(graph, "San Francisco"))
        fprintf(stderr, "Failed to add \"San Francisco\"\n");

    return (EXIT_SUCCESS);
}
```

### 2. Add an edge

`2-graph_add_edge.c`

This function adds an edge between two vertices in an existing graph.

```c
int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type);
```

*   `graph`: A pointer to the graph to add the edge to.
*   `src`: The string identifying the source vertex.
*   `dest`: The string identifying the destination vertex.
*   `type`: The type of edge (`UNIDIRECTIONAL` or `BIDIRECTIONAL`).

**Return:** `1` on success, or `0` on failure.

**Notes:**
*   On failure, no edge must be created, and there must be no memory leak.
*   If either `src` or `dest` vertices are not found in the graph, the function must fail.

**Example Usage:**

```c
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

// Assuming graph_create, graph_add_vertex, and graph_display are available.

int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    return (EXIT_SUCCESS);
}
```

### 3. Delete graph

`3-graph_delete.c`

This function completely deallocates all memory associated with a graph.

```c
void graph_delete(graph_t *graph);
```

*   `graph`: A pointer to the graph to be deleted.

**Notes:**
*   This function must delete all vertices, edges, and the graph structure itself.

**Example Usage:**

```c
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

// Assuming graph_create, graph_add_vertex, graph_add_edge, and graph_display are available.

int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    graph_delete(graph); // Delete the graph

    return (EXIT_SUCCESS);
}
```

### 4. Depth-first traversal

`4-depth_first_traverse.c`

This function traverses a graph using the Depth-First Search (DFS) algorithm.

```c
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));
```

*   `graph`: A pointer to the graph to traverse. The traversal must start from the first vertex in the `vertices` list.
*   `action`: A pointer to a function to be called for each visited vertex.
    *   `v`: A `const` pointer to the visited vertex.
    *   `depth`: The depth of `v` from the starting vertex.

**Return:** The biggest vertex depth reached during the traversal, or `0` on failure.

**Example Usage:**

```c
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

// Helper function for display
void traverse_action(const vertex_t *v, size_t depth)
{
    printf("%*s[%lu] %s\n", (int)depth * 4, "", v->index, v->content);
}

int main(void)
{
    graph_t *graph;
    size_t depth;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    printf("\nDepth First Traversal:\n");
    depth = depth_first_traverse(graph, &traverse_action);
    printf("\nDepth: %lu\n", depth);

    graph_delete(graph);

    return (EXIT_SUCCESS);
}
```

### 5. Breadth-first traversal

`5-breadth_first_traverse.c`

This function traverses a graph using the Breadth-First Search (BFS) algorithm.

```c
size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));
```

*   `graph`: A pointer to the graph to traverse. The traversal must start from the first vertex in the `vertices` list.
*   `action`: A pointer to a function to be called for each visited vertex.
    *   `v`: A `const` pointer to the visited vertex.
    *   `depth`: The depth of `v` from the starting vertex.

**Return:** The biggest vertex depth reached during the traversal, or `0` on failure.

**Example Usage:**

```c
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

// Helper function for display
void traverse_action(const vertex_t *v, size_t depth)
{
    printf("%*s[%lu] %s\n", (int)depth * 4, "", v->index, v->content);
}

int main(void)
{
    graph_t *graph;
    size_t depth;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    printf("\nBreadth First Traversal:\n");
    depth = breadth_first_traverse(graph, &traverse_action);
    printf("\nDepth: %lu\n", depth);

    graph_delete(graph);

    return (EXIT_SUCCESS);
}
```
```