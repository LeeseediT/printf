#include "main.h"



/**
 * _size - gets special  values
 * @format: gets the specifier passed
 * @i: List of arguments to be printed.
 * Return: 1 or 2;
 */
int _size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = SIZE_LONG;
	else if (format[curr_i] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
/**
 * _width - gets special  values
 * @format: gets the specifier passed
 * @i: List of arguments to be printed.
 * @list: variadic list
 * Return: 1 or 2;
 */
int _width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}


/**
 * int_size - adjusts the size of an integer
 * @num: the int to be adjusted
 * @size: size int to be checked.
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
 * @num: the int to be adjusted
 * @size: size int to be checked.
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

