0x11.C Understanding and using printf

#**0x11.C-printf**
###

0x11.C-printf is a C program that emulates the functionality of the printf() function in the standard C library. This program takes in a format string and a variable number of arguments and outputs a formatted string to the console.

Requirements
This program was developed and tested on a Unix-based system (Ubuntu 20.04 LTS). To run this program, you will need:

A C compiler (gcc or clang)
Unix-based operating system (Linux or MacOS)
Usage
To use this program, clone this repository and compile the main.c file:

bash
Copy code
[git clone](https://github.com/LeeseediT/printf.git) https://github.com/LeeseediT/printf.git
**cd 0x11.C-printf**
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c
Then, execute the compiled file with the desired format string and arguments:

bash
Copy code
`./a.out "Hello, %s!" "world"`
This will output:

Copy code
Hello, world!
Supported Format Specifiers
The following format specifiers are supported in this program:

- %c - char
- %s - string
- %d - decimal integer
- %i - integer (same as %d)
- %u - unsigned decimal integer
- %o - octal integer
- %x - hexadecimal integer (lowercase)
- %X - hexadecimal integer (uppercase)
- %p - pointer address
Example
Here is an example of how to use this program:

arduino
Copy code
```C
#include "main.h"

int main(void)
{
    int num = 123;
    char *str = "hello";
    void *ptr = &num;

    _printf("String: %s, Integer: %d, Address: %p\n", str, num, ptr);

    return (0);
}
This will output:

yaml
Copy code
String: hello, Integer: 123, Address: 0x7ffeed9b0b24
###Limitations
This program does not support all of the format specifiers that the standard printf() function supports. Additionally, it does not handle errors as gracefully as the standard printf() function does. It is recommended to use this program only for simple string formatting.