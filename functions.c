#include "main.h"

/**
 * _specifiers - gets special  values
 * @format: gets the specifier passed
 * @i: List of arguments to be printed.

 * Return: 1 or 2;
 */

int _specifiers(const char *format, int *i)
{

	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {MINUS_FLAG, PLUS_FLAG, ZERO_FLAG, HASH_FLAG, SPACE_FLAG, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
/**
 * _precision - gets special  values
 * @format: gets the specifier passed
 * @i: List of arguments to be printed.
 *@list: variadic list
 * Return: 1 or 2;
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
