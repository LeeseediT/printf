#include "main.h"
/**
 * is_printable - Prints a value of its format
 * @c: character to be checked
 * Return: 1 or 2;
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa - Prints a value of its format
 * @ascii_code: Formatted string in which to print the arguments.
 * @buffer: List of arguments in the memory to be printed.
 * @ind: buffer index
 * Return: 1 or 2;
 */
int append_hexa(char ascii_code, char buffer[], int ind)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
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
 * int_size - adjusts the size of an integer
 * @num: the int to be adjusted
 * @list: List of arguments to be printed.
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
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
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
