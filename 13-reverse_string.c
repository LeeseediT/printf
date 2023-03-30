#include "main.h"


/**
 *reverse_str - takes in a va_list object which contains
 *		a single argument of type char*, and then prints
 *		the characters of the string in reverse order.
 *@types: argument, which is used to access the
 *			variable argument list.
 *@buffer: represents a buffer where the formatted
 *			output will be stored.
 *@flags: represents any optional formatting flags that are
 *			used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits
 *			after the flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer
 *			that is passed as an argument.
 *Return: returns an integer value representing the
 *			number of characters written to the output buffer.
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
