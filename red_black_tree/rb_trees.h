#ifndef rb_trees
#define rb_trees
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	RED = 0,
	BLACK = 1
} rb_color_t;

/**
 * struct rb_tree - red-black tree node
 * @value: value of current node
 * @parent: parent node of current node
 * @left: left node of current node
 * @right: right node of current node
 * @color: red-black color of current node
 */
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