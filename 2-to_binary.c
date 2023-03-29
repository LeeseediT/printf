#include "main.h"

/**
 *_binary - Prints a value of its format
 *@buffer: represents a buffer where the
 *			formatted output will be stored.
 *@types: argument, which is used to access
 *			the variable argument list.
 *@flags: represents any optional formatting
 *			flags that are used in the printf-style function call.
 *@width: represents the minimum field width for the output character..
 *@precision: used to specify the number of digits after the
 *			flag characters for non-custom conversion specifier values.
 *@size:  represents the maximum size of the buffer that is
 *		passed as an argument.
 *Return: returns an integer value representing the number of characters
 *			written to the output buffer.
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
