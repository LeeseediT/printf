#include "main.h"
/**
 *_size - a helper function used to parse format
 *			strings and determine the size of a format specifier.
 *@format: a pointer to a character array
 *			representing the format string being parsed.
 *@i:  a pointer to an integer value representing the
 *		current position in the format string being parsed.
 *Return: returns the calculated size.
 */
int _size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = SIZE_LONG;
	else if (format[curr_i] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
/**
 *_width - parses the format string to find the minimum
 *		field width for the output character and returns that value
 *@format: a pointer to a character array representing
 *			the format string being parsed.
 *@i: a pointer to an integer value representing the current
 *			position in the format string being parsed.
 *@list: a variable argument list containing the arguments to be formatted.
 *Return: returns the width and updates the current index pointer to point to
 *		the last character processed. If there is no width specified, the
 *		function returns 0.
 */
int _width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}

/**
 *int_size - to cast a number to a specific size based
 *		on the size argument passed to it.
 *@num: an integer value that is being
 *			converted to a different data type based on
 *			the size parameter.
 *@size: specifies the desired data type size to which
 *			the num parameter should be converted.
 *Return: returns the converted integer
 */

long int int_size(long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 *unsigned_int_size - convert an unsigned integer to a
 *		different type of unsigned integer based on the specified size.
 *@num: an unsigned integer value that is being
 *			converted to a different data type based on
 *			the size parameter.
 *@size: specifies the desired data type size to
 *			which the num parameter should be converted.
 *Return: returns an integer value representing the
 *			number of characters written to the output buffer.
 */
long int unsigned_int_size(unsigned long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

/**
 *write_unsigned - writes an unsigned integer to a buffer using the
 *		specified format. It takes in the following parameters:
 *@buffer: represents a buffer where the formatted output will be stored.
 *@flags: represents any optional formatting flags
 *			that are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@is_negative: checks if the in it a negative int
 *@ind: an integer value that represents the buffer index where
 *		the integer should be written.
 *@size: an integer value representing the size of the integer
 *@precision: used to specify the number of digits after the flag
 *				characters for non-custom conversion specifier values.
 *Return: returns an integer value representing
 *				the number of characters written to the output buffer.
 */

int write_unsigned(int is_negative, int ind,
				   char buffer[],
				   int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1, i = 0;
	char padd = ' ';

	(void)is_negative;
	(void)size;

	if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & ZERO_FLAG) && !(flags & MINUS_FLAG))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & MINUS_FLAG)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}
