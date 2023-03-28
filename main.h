#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#define BUFFER_SIZE 1024

#define MINUS_FLAG 1
#define PLUS_FLAG 2
#define ZERO_FLAG 4
#define HASH_FLAG 8
#define SPACE_FLAG 16
#define SIZE_LONG 2
#define SIZE_SHORT 1

typedef struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
} fmt_type;

int _printf(const char *format, ...);
void print_buffer(char buffer[], int *buff_ind);
int _specifier(const char *fmt, int *arg_list,
				 va_list list, char buffer[], int flags, int width, int precision, int size);
int get_flags(const char *format, int *arg_list);
int get_width(const char *format, int *arg_list, va_list list);
int get_precision(const char *format, int *arg_list, va_list list);
int get_size(const char *format, int *arg_list);


int _char(va_list types, char buffer[],
		  int flags, int width, int precision, int size);
int _string(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int _percent(va_list types, char buffer[],
			 int flags, int width, int precision, int size);

#endif
