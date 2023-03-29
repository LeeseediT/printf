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
	const int FLAGS_ARR[] = {MINUS_FLAG, PLUS_FLAG, ZERO_FLAG,
							HASH_FLAG, SPACE_FLAG, 0};

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
 * is_digit - checks if a value is a digit
 * @c: character to check
 * Return: 1 or 2;
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
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
