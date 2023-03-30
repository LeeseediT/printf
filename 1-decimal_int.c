#include "main.h"

/**
 *is_digit - checks if a value is a digit
 *@c: character to check
 *Return: returns an integer value representing the
 *			number of characters written to the output buffer.
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 *_int - is responsible for handling the conversion specifier "d" or "i",
 *		which formats and prints an integer.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@types: variadic list
 *@flags: represents any optional formatting flags
 *			that are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the flag
 *				characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is passed
 *		as an argument.
 *Return: returns an integer value representing
 *				the number of characters written to the output buffer.
 */

int _int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = int_size(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_integer(is_negative, i, buffer, flags, width, precision, size));
}



/**
 *write_integer - is responsible for writing an integer to a buffer and
 *		applying any necessary padding and precision.
 *@is_negative: to check if an int is negative
 *@ind: buffer index
 *@buffer: represents a buffer where the formatted output
 *		will be stored.
 *@flags: represents any optional formatting flags that
 *		are used in the printf-style function call.
 *@width: represents the minimum field width for the output
 *		character..
 *@precision: used to specify the number of digits after
 *		the flag characters for non-custom conversion specifier values.
 *@size: integer size
 *Return: returns an integer value representing the number of
 *		characters written to the output buffer.
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
 *write_int - is used to write integer values to the output buffer.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@ind: represents the current index into the output
 *			buffer where the next character should be written.
 *@flags: represents any optional formatting flags that are used
 *			in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the flag
 *			characters for non-custom conversion specifier values.
 *@length:  represents the maximum size of the buffer that is
 *			passed as an argument.
 *@padd: is used to specify the padding character to use when filling
 *			the output string to the specified width.
 *@extra_c: Extra char
 *Return: returns an integer value representing the number of
 *			characters written to the output buffer.
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
