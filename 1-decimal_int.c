#include "main.h"



/**
 * print_hexa - Prints a value of its format
  * @types: argument, which is used to access the variable argument list.
 * @buffer: represents a buffer where the formatted output will be stored.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @map_to: array of strings
 * @width: represents the minimum field width for the output character..
 * @flag_ch: flag character to be used
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size:  represents the maximum size of the buffer that is passed as an argument.
 * Return: number of values printed;
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	(void)width;

	num = unsigned_int_size(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & HASH_FLAG && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;
	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}


/**
 * write_unsigned - get an un signed int passed using the specifier
 * @buffer: represents a buffer where the formatted output will be stored.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @is_negative: checks if the in it a negative int
 * @ind: buffer index of value
 * @size: size of the integer
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * Return: number of values printed;
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

/**
 * write_pointer - Prints a value of its format
 * @ind: Index at which the number starts on the buffer
 * @buffer: represents a buffer where the formatted output will be stored.
 * @flags: Flags
 * @width: width
 * @padd_start: character padding start
 * @length: Number length
 * @padd: Padding character
 * @extra_c: Extra char
 *
 * Return: number of values printed;
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
 * _int - Prints a value of its format
 * @buffer: represents a buffer where the formatted output will be stored.
 * @types: variadic list
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size:  represents the maximum size of the buffer that is passed as an argument.
 * Return: number of values printed;
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
