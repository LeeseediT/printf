#include "main.h"


/**
 * _char - Prints a value of its format
 * @buffer: represents a buffer where the formatted output will be stored.
 * @types: argument, which is used to access the variable argument list.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size:  represents the maximum size of the buffer that is passed as an argument.
 * Return: returns an integer value representing the number of characters written to the output buffer.


 */




int _char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * _string - Prints a value of its format
 * @buffer: represents a buffer where the formatted output will be stored.
 * @types: argument, which is used to access the variable argument list.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size:  represents the maximum size of the buffer that is passed as an argument.
 * Return: returns an integer value representing the number of characters written to the output buffer.


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
 * @buffer: represents a buffer where the formatted output will be stored.
 * @types: argument, which is used to access the variable argument list.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size:  represents the maximum size of the buffer that is passed as an argument.
 * Return: returns an integer value representing the number of characters written to the output buffer.


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

