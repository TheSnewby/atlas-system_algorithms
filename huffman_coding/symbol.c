#include "huffman.h"

/**
 * symbol_create - creates a symbol data structure
 * @data: data to be stored
 * @freq: associated frequency
 *
 * Return: new symbol or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *new = NULL;

	new = (symbol_t *)malloc(sizeof(symbol_t));
	if (!new)
		return (NULL);

	new->data = data;
	new->freq = freq;

	return (new);
}
