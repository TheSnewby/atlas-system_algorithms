#ifndef rb_trees
#define rb_trees
#include <stdio.h>

typedef enum
{
	RED = 0,
	BLACK = 1
} rb_color_t;

typedef struct rb_tree
{
	int value;
	struct rb_tree *parent;
	struct rb_tree *left;
	struct rb_tree *right;
	rb_color_t color;
} rb_tree_t;

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);


#endif