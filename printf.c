#include "main.h"
/**
 * _printf -emulates the printf() built in function
 * @format: passed identifier
 *
 * @...: variadic argument
 * Return: returns the number of printed values
 */
int _printf(const char *format, ...)
{
	int i = 0, printed = 0, num_printed = 0;
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

			num_printed++;
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
			num_printed += printed;
		}
		i++;
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (num_printed);
}

/**
 * func_print - gets the function to each specifier required input  formatting
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be checked.
 * @ind: index of search.
 * @buffer: Buffer array to handle printing.
 * @flags: represents any optional formatting flags that are used in the printf-style function call.
 * @width: represents the minimum field width for the output character..
 * @precision: used to specify the number of digits after the flag characters for non-custom conversion specifier values.
 * @size:  represents the maximum size of the buffer that is passed as an argument.
 * Return: returns an integer value representing the number of characters written to the output buffer.


 */
int func_print(const char *fmt, int *ind, va_list list, char buffer[],
			   int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, num_printed = -1;
	fmt_t fmt_types[] = {
		{'c', _char}, {'s', _string}, {'%', _percent},
		{'i', _int}, {'d', _int}, {'b', _binary}, {'u', _unsigned},
		{'o', _octal}, {'x', _hexa}, {'X', hexa_upper}, {'p', _pointer},
		{'S', _unprintable}, {'r', reverse_str}, {'R', _rot13}, {'\0', NULL}};

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
	return (num_printed);
}
