#include "main.h"
/**
 * _printf -emulates the printf() built in function
 * @format: passed identifier
 * 
 * @...: variadic argument
 */
int _printf(const char *format, ...)
{
	int i = 0, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	while (format[i])
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFER_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = _specifiers(format, &i);
			width = _width(format, &i, list);
			precision = _precision(format, &i, list);
			size = _size(format, &i);
			++i;
			printed = func_print(format, &i, list, buffer,
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
 * print_buffer - prints out the values stored in the buffer
 * @buffer: Array of chars values
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

/**
 * func_print - prints values depending on the specifier passed
 * 
 * 
 * 
 */

int func_print(const char *fmt, int *ind, va_list list, char buffer[],
			   int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', _char}, {'s', _string}, {'%', _percent}, {'i', _int}, {'d', _int},
		{'b', _binary}, {'u', _unsigned}, {'o', _octal}, {'x', _hexa}, {'X', hexa_upper},
		{'p', _pointer}, {'S', _unprintable}, {'r', reverse_str}, {'R', _rot13}, {'\0', NULL}};


	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
