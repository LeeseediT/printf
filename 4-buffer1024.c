#include "main.h"


/**
 * print_buffer - prints a values stored in the buffer memory
 * @buffer: Array of chars values in the buffer
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
