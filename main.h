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
/**
 * fmt - a struct data type
 * @fmt_t: variable from fmt struct.
 * 
 * 
 */
typedef struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
} fmt_t;

int _printf(const char *format, ...);
int func_print(const char *fmt, int *i, va_list list, char buffer[],
			   int flags, int width, int precision, int size);
void print_buffer(char buffer[], int *buff_ind);

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

int print_hexa(va_list types, char map_to[], char buffer[], int flags,
			   char flag_ch, int width, int precision, int size);

int _unprintable(va_list types, char buffer[],
				 int flags, int width, int precision, int size);

int _pointer(va_list types, char buffer[],
			 int flags, int width, int precision, int size);

int _specifiers(const char *format, int *i);
int _width(const char *format, int *i, va_list list);
int _precision(const char *format, int *i, va_list list);
int _size(const char *format, int *i);

int reverse_str(va_list types, char buffer[],
				int flags, int width, int precision, int size);

int _rot13(va_list types, char buffer[],
		   int flags, int width, int precision, int size);

int handle_write_char(char c, char buffer[],
					  int flags, int width, int precision, int size);
int write_integer(int is_positive, int ind, char buffer[],
				 int flags, int width, int precision, int size);
int write_int(int ind, char bff[], int flags, int width, int precision,
			  int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length, int width,
				  int flags, char padd, char extra_c, int padd_start);

int write_unsigned(int is_negative, int ind,
				 char buffer[],
				 int flags, int width, int precision, int size);

int is_printable(char);
int append_hexa(char, char[], int);
int is_digit(char);

long int int_size(long int num, int size);
long int unsigned_int_size(unsigned long int num, int size);

#endif
