#include "main.h"
#include <stdarg.h>
/**
 * _printf - emulates the builtin printf() function
 *@format: specifier within the passed string
 *@...: variadic arguments
 *Return: return number of values printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	const char *p = format;

	va_start(args, format);

	while (*p)
	{
		if (*p == '%')
		{
			p++;
			switch (*p)
			{
			case 'c':
				_putchar(va_arg(args, int));
				printed_chars++;
				break;
			case 's':
			{
				const char *s = va_arg(args, const char *);

				while (*s)
				{
					_putchar(*s);
					s++;
					printed_chars++;
				}
				break;
			}
			case '%':
				_putchar('%');
				printed_chars++;
				break;
			default:
				_putchar('%');
				_putchar(*p);
				printed_chars += 2;
				break;
			}
		}
		else
		{
			_putchar(*p);
			printed_chars++;
		}
		p++;
	}

	va_end(args);
	return (printed_chars);
}
