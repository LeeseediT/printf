#include "main.h"

/**
 * _pointer - Prints a value of its format
 * @types: argument, which is used to access the variable argument list.
 * @buffer: represents a buffer where the formatted output will be stored.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size:  represents the maximum size of the buffer that is passed as an argument.
 * Return: returns an integer value representing the number of characters written to the output buffer.


 */

int _pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFFER_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	(void)width;
	(void)size;

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	(void)precision;

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & ZERO_FLAG) && !(flags & MINUS_FLAG))
		padd = '0';
	if (flags & PLUS_FLAG)
		extra_c = '+', length++;
	else if (flags & SPACE_FLAG)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}
