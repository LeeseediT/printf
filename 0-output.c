#include "main.h"

/**
 *_char - is used to handle the conversion specifier %c in the
 *		printf function.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@types: argument, which is used to access the variable argument list.
 *@flags: represents any optional formatting
 *		flags that are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after
 *			the flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the
 *			buffer that is passed as an argument.
 *Return: returns an integer value representing
 *				the number of characters written to the output buffer.
 */

int _char(va_list types, char buffer[],
		  int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 *_string - is responsible for handling the formatting and printing of
 *		strings using the %s specifier.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@types: argument, which is used to access the variable argument list.
 *@flags: represents any optional formatting
 *		flags that are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after
 *			the flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the
 *			buffer that is passed as an argument.
 *Return: returns an integer value representing
 *				the number of characters written to the output buffer.
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
 *_percent - is a printf format specifier function that handles
 *		the % format specifier
 *@buffer: represents a buffer where the formatted output will be stored.
 *@types: argument, which is used to access the variable argument list.
 *@flags: represents any optional formatting
 *		flags that are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after
 *			the flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the
 *			buffer that is passed as an argument.
 *Return: returns an integer value representing
 *				the number of characters written to the output buffer.
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
 *handle_write_char - This function handles the printing
 *		of a single character.
 *@c: character to be handles
 *@buffer: represents a buffer where the formatted
 *		output will be stored.
 *@flags: represents any optional formatting flags that
 *		are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the
 *		flag characters for non-custom conversion specifier values.
 *@size: integer size
 *Return: returns an integer value representing the number of
 *		characters written to the output buffer.
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
