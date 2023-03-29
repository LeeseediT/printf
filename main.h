#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#define BUFF_SIZE 1024

#define MINUS_FLAG 1
#define PLUS_FLAG 2
#define ZERO_FLAG 4
#define HASH_FLAG 8
#define SPACE_FLAG 16

#define S_LONG 2
#define S_SHORT 1

typedef struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
}fmt_type;

int _printf(const char *format, ...);
int get_formats(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);


int _char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int _string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int _percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int _int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int _binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int _unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int _octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int _hexa(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int _pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

int _reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int _rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);

int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif
