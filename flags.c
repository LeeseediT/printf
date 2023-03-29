#include "main.h"

/**
 * _char - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */




int _char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * _string - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int _string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & MINUS_FLAG)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * _percent - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int _percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	(void)types;
	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;
	return (write(1, "%%", 1));
}


/**
 * _int - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
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

	return (write_intber(is_negative, i, buffer, flags, width, precision, size));
}
/**
 * _binary - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */



int _binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}


/**
 * _unsigned - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int _unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = unsigned_int_size(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * _octal - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int _octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
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
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & HASH_FLAG && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * _hexa - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int _hexa(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * hexa_upper - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
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

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


#include "main.h"

/**
 * _pointer - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
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
 * _unprintable - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int _unprintable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * reverse_str - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int reverse_str(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	(void)buffer;
	(void)flags;
	(void)width;
	(void)size;

	str = va_arg(types, char *);

	if (str == NULL)
	{
		(void)precision;

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**
 * _rot13 - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int _rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
/**
 * is_printable - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int append_hexa(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * int_size - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
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
 * unsigned_int_size - Prints a value of its format
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
long int unsigned_int_size(unsigned long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
