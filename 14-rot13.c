#include "main.h"

/**
 *_rot13 - Prints a value of its format
 *@types: argument, which is used to access the
 *			variable argument list.
 *@buffer: represents a buffer where the formatted
 *			output will be stored.
 *@flags: represents any optional formatting flags that are
 *			used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the
 *			flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer
 *		that is passed as an argument.
 *Return: returns an integer value representing the number of
 *			characters written to the output buffer.
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
