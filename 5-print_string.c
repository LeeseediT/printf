#include "main.h"

/**
 *_unprintable - extracts a string from the argument
 *		list and checks each character in the string
 *		to see if it is a printable character using
 *		the is_printable function.
 *@types: List of arguments to be printed..
 *@buffer: represents a buffer where the formatted
 *			output will be stored.
 *@flags: represents any optional formatting flags that are
 *			used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after
 *			the flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer
 *			that is passed as an argument.
 *Return: returns an integer value representing the number of
 *			characters written to the output buffer.
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
 *is_printable - checks if a character is printable
 *@c:  represents a single character that is being
 *		tested for printability.
 *Return: returns 1 if the character is a printable
 *		ASCII character (i.e., its ASCII code is in
 *		the range 32-126), and 0 otherwise.
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 *append_hexa - returns the number of characters appended to the buffer
 *		(always 3, since a hexadecimal representation is two characters
 *		preceded by '\x').
 *@ascii_code: Formatted string in which to print the arguments.
 *@buffer: represents a buffer where the formatted output will be stored.
 *@ind: represents the current index into the output
 *			buffer where the next character should be written.
 *Return: returns an integer value representing
 *			the number of characters written to the output buffer.
 */
int append_hexa(char ascii_code, char buffer[], int ind)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		/* ascii_code *= -1; */

	buffer[ind++] = '\\';
	buffer[ind++] = 'x';

	buffer[ind++] = map_to[ascii_code / 16];
	buffer[ind] = map_to[ascii_code % 16];

	return (3);
}
