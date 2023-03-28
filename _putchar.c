#include "main.h"
/**
 * _putchar - prints a single character to standard output
 * @c: character to be printed
 * Return: always 1
 */
int _putchar(char c)
{
    return(write(1, &c, 1));
}