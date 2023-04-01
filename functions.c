#include "main.h"


/**
 * print_char - Prints a character
 * @types: List of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: Width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char d = va_arg(types, int);

	return (handle_write_char(d, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width.
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
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
 * print_percent - Prints a percent sign
 * @types: Lists of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Prints int
 * @types: Lists of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * @types: Lists of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Numbers of char printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int p, m, q, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	p = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = p / m;
	for (q = 1; q < 32; q++)
	{
		m /= 2;
		a[q] = (p / m) % 2;
	}
	for (q = 0, sum = 0, count = 0; q < 32; q++)
	{
		sum += a[q];
		if (sum || q == 31)
		{
			char z = '0' + a[q];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}






