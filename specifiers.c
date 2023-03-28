#include "main.h"

int _specifier(const char *fmt, int *index, va_list list, char buffer[],
				 int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_type fmt_typeypes[] = {
		{'c', _char}, {'s', _string}, {'%', _percent}, {'\0', NULL}};
	for (i = 0; fmt_typeypes[i].fmt != '\0'; i++)
		if (fmt[*index] == fmt_typeypes[i].fmt)
			return (fmt_typeypes[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_typeypes[i].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		unknow_len += write(1, &fmt[*index], 1);
		return (unknow_len);
	}
	return (printed_chars);
}

/**
 * _char - function that handles the %c specifier
 * @types: the data type of the value
 * @buffer: a buffer array
 * @flags: the flags in the string
 * @width: handles the with specified in the string
 * @precision: handles string precision
 * @size: handles the size specified in the string
 * Return: returns the number of printed values
 */
int _char(va_list types, char buffer[],
		  int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**
 * _string - function that handles the %c specifier
 * @types: the data type of the value
 * @buffer: a buffer array
 * @flags: the flags in the string
 * @width: handles the with specified in the string
 * @precision: handles string precision
 * @size: handles the size specified in the string
 * Return: returns the number of printed values
 */
int _string(va_list types, char buffer[],
			int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & MINUS_FLAG)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/**
 * _modulus - function that handles the %c specifier
 * @types: the data type of the value
 * @buffer: a buffer array
 * @flags: the flags in the string
 * @width: handles the with specified in the string
 * @precision: handles string precision
 * @size: handles the size specified in the string
 * Return: returns the number of printed values
 */
int _modulus(va_list types, char buffer[],
			 int flags, int width, int precision, int size)
{
	(void)types;
	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;
	return (write(1, "%%", 1));
}
