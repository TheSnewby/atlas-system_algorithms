#ifndef nary_trees_h
#define nary_trees_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct nary_tree_s - N-ary tree node structure
 *
 * @content: Content of the node
 * @parent: Pointer to the parent node
 * @nb_children: Number of children
 * @children: Pointer to the head node of the children linked list
 * @next: Pointer to the next child in the parent's children linked list
 */
typedef struct nary_tree_s
{
    char            *content;
    struct nary_tree_s  *parent;
    size_t          nb_children;
    struct nary_tree_s  *children;
    struct nary_tree_s  *next;
} nary_tree_t;

nary_tree_t *nary_tree_insert(nary_tree_t *, char const *);
void nary_tree_delete(nary_tree_t *);
size_t nary_tree_traverse(nary_tree_t const *, void (*)(nary_tree_t const *, size_t ));
size_t nary_tree_diameter(nary_tree_t const *);
int path_exists(nary_tree_t const *, char const * const *);

#endif
