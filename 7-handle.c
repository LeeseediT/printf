#include "main.h"

/**
 * write_integer - Prints a value  based on its format
 * @is_negative: to check if an int is negative
 * @ind: buffer index
 * @buffer: represents a buffer where the formatted output will be stored.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size: integer size
 * Return: returns an integer value representing the number of characters written to the output buffer.


 */
int write_integer(int is_negative, int ind, char buffer[],
				 int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	(void)size;

	if ((flags & ZERO_FLAG) && !(flags & MINUS_FLAG))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & PLUS_FLAG)
		extra_ch = '+';
	else if (flags & SPACE_FLAG)
		extra_ch = ' ';

	return (write_int(ind, buffer, flags, width, precision,
					  length, padd, extra_ch));
}




/**
 * handle_write_char - Prints a value of its format
 * @c: character to be handles
 * @buffer: represents a buffer where the formatted output will be stored.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size: integer size
 * Return: returns an integer value representing the number of characters written to the output buffer.


 */
int handle_write_char(char c, char buffer[], int flags, int width,
					  int precision, int size)
{

	int i = 0;
	char padd = ' ';

	(void)precision;
	(void)size;

	if (flags & ZERO_FLAG)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER_SIZE - i - 2] = padd;

		if (flags & MINUS_FLAG)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}


/**
 * write_int - Prints a value of its format
 * @buffer: represents a buffer where the formatted output will be stored.
 * @ind: character index in the buffer
 * @flags: specifier passed
 * @width: width
 * @precision: search method
 * @length: Number length
 * @padd: Padding character
 * @extra_c: Extra char
 * Return: returns an integer value representing the number of characters written to the output buffer.


 */

int write_int(int ind, char buffer[], int flags, int width, int precision,
			  int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (precision == 0 && ind == BUFFER_SIZE - 2
		&& buffer[ind] == '0' && width == 0)
		return (0);
	if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';

	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & MINUS_FLAG && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & MINUS_FLAG) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & MINUS_FLAG) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}
