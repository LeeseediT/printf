#include "main.h"



/**
 *write_pointer - Prints a value of its format
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



/**
 *_int - Prints a value of its format
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
 *write_integer - Prints a value  based on its format
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
