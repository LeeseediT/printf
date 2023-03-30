#include "main.h"
/**
 *_putchar - takes a single character as
 *		input and writes it to standard output using
 *		the write system call.
 *@c: character to be printed
 *Return: always 1
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
