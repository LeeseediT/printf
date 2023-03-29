#include "main.h"


/**
 *is_digit - checks if a value is a digit
 *@c: character to check
 *Return: returns an integer value representing the
 *			number of characters written to the output buffer.
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 *_precision - gets special  values
 *@format: gets the specifier passed
 *@i: List of arguments to be printed.
 *@list: variadic list
 *Return: returns an integer value representing the number
 *			of characters written to the output buffer.
 */

int _precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
		return (precision);

	precision = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (precision);
}
