#include "main.h"

/**
 *_pointer - is a implementation of the conversion specifier %p which
 *		is used to print the memory address of a pointer in hexadecimal
 *		format.
 *@types: argument, which is used to access the variable argument list.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@flags: represents any optional formatting flags that are used
 *			in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the flag
 *			characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is
 *			passed as an argument.
 *Return: returns an integer value representing the number
 *			of characters written to the output buffer.
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


/**
 *write_pointer - is used to write a hexadecimal pointer address to
 *		a buffer with a given width and flags.
 *@ind: represents the current index into the output buffer
 *			where the next character should be written.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@flags: represents any optional formatting flags
 *			that are used in the printf-style function call.
 *@width: width
 *@padd_start: is used to control where padding characters
 *				are inserted in the output string.
 *@length: Number length
 *@padd: is used to specify the padding character
 *			to use when filling the output string to the specified width.
 *@extra_c: Extra char
 *
 *Return: returns an integer value representing
 *				the number of characters written to the output buffer.
 */

int write_pointer(char buffer[], int ind, int length,
				  int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & MINUS_FLAG && padd == ' ')

		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & MINUS_FLAG) && padd == ' ')

		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & MINUS_FLAG) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFFER_SIZE - ind - 1));
}

