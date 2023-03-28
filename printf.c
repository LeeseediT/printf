#include "main.h"
/**
 *_printf - emulates the builtin function printf()
 * @format: the specifier passed in the string
 * @...: variadic arguments
 */

int _printf(const char *format, ...)
{
	int i = 0, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	while (format[i])
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFFER_SIZE)
				print_buffer(buffer, &buff_ind);
			write(1, &format[i], 1);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = _specifier(format, &i, list, buffer,
								   flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
		i++;
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - print a buffer contents in standard output
 *
 * @buffer: characters to print from the buffer
 *
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

/**
 * get_flags - gets the flags passed in the string
 * @format: the format to get the flags
 *
 *
 */
int get_flags(const char *format, int *arg_list)
{
	int j, curr_item;
	int flags = 0;
	const char FLAGS_VAL[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAG_VAR[] = {MINUS_FLAG, PLUS_FLAG, ZERO_FLAG, HASH_FLAG, SPACE_FLAG, 0};

	for (curr_item = *arg_list + 1; format[curr_item] != '\0'; curr_item++)
	{
		while (FLAGS_VAL[j])
		{
			if (format[curr_item] == FLAGS_VAL[j])
			{
				flags |= FLAG_VAR[j];
				break;
			}
			j++;
		}

		if (FLAGS_VAL[j] == 0)
			break;
	}

	*arg_list = curr_item - 1;

	return (flags);
}

/**
 * get_width - gets the width of the string passed in the string
 * @format: the format specifier passed in the string
 * @
 */
int get_width(const char *format, int *arg_list, va_list list)
{
	int curr_item;
	int width = 0;

	for (curr_item = *arg_list + 1; format[curr_item] != '\0'; curr_item++)
	{
		if (is_digit(format[curr_item]))
		{
			width *= 10;
			width += format[curr_item] - '0';
		}
		else if (format[curr_item] == '*')
		{
			curr_item++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*arg_list = curr_item - 1;

	return (width);
}

int get_size(const char *format, int *arg_list)
{
	int curr_item = *arg_list + 1;
	int size = 0;

	if (format[curr_item] == 'l')
		size = SIZE_LONG;
	else if (format[curr_item] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*arg_list = curr_item - 1;
	else
		*arg_list = curr_item;

	return (size);
}

int get_precision(const char *format, int *arg_list, va_list list)
{
	int curr_item = *arg_list + 1;
	int precision = -1;

	if (format[curr_item] != '.')
		return (precision);

	precision = 0;

	for (curr_item += 1; format[curr_item] != '\0'; curr_item++)
	{
		if (is_digit(format[curr_item]))
		{
			precision *= 10;
			precision += format[curr_item] - '0';
		}
		else if (format[curr_item] == '*')
		{
			curr_item++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*arg_list = curr_item - 1;

	return (precision);
}
