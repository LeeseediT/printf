#include "main.h"




/**
 *print_hexa - Prints a value of its format
 *@types: argument, which is used to access the variable argument list.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@flags: represents any optional formatting flags
 *			that are used in the printf-style function call.
 *@map_to: array of strings
 *@width: represents the minimum field width for the output character..
 *@flag_ch: flag character to be used
 *@precision: used to specify the number of digits after the flag
 *				characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is passed
 *		as an argument.
 *Return: returns an integer value representing
 *				the number of characters written to the output buffer.
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
 *_octal - Prints a value of its format
 *@types: argument, which is used to access the variable argument list.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@flags: represents any optional formatting flags that are
 *			used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the
 *			flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is passed as an argument.
 *Return: returns an integer value representing the number of
 *			characters written to the output buffer.
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

	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}




/**
 *_unsigned - Prints a value of its format
 *@types: argument, which is used to access the
 *			variable argument list.
 *@buffer: represents a buffer where the formatted
 *			output will be stored.
 *@flags: represents any optional formatting flags
 *			that are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the
 *			flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is passed as an argument.
 *Return: returns an integer value representing the number
 *			of characters written to the output buffer.
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

	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}



/**
 *_hexa - Prints a value of its format
 *@types: argument, which is used to access the
 *			variable argument list.
 *@buffer: represents a buffer where the formatted
 *			output will be stored.
 *@flags: represents any optional formatting flags
 *			that are used in the printf-style function call.
 *@width: represents the minimum field width for the
 *			output character..
 *@precision: used to specify the number of digits after
 *				the flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is
 *			passed as an argument.
 *Return: returns an integer value representing the number
 *			of characters written to the output buffer.
 */

int _hexa(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}


/**
 *hexa_upper - Prints a value of its format
 *@types: argument, which is used to access the variable
 *			argument list.
 *@buffer: represents a buffer where the formatted output
 *			will be stored.
 *@flags: represents any optional formatting flags that are
 *			used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the
 *				flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is
 *			passed as an argument.
 *Return: returns an integer value representing the number of
 *			characters written to the output buffer.
 */

int hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}
