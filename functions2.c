#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @types: Lists of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char cha_d = 0, padd = ' ';
	int indr = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[indr--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		cha_d = '+', length++;
	else if (flags & F_SPACE)
		cha_d = ' ', length++;

	indr++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, indr, length,
		width, flags, padd, cha_d, padd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lists of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int g = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[g] != '\0')
	{
		if (is_printable(str[g]))
			buffer[g + offset] = str[g];
		else
			offset += append_hexa_code(str[g], buffer, g + offset);

		g++;
	}

	buffer[g + offset] = '\0';

	return (write(1, buffer, g + offset));
}

/**
 * print_reverse - Prints reverse of a string.
 * @types: Lists of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int g, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (g = 0; str[g]; g++)
		;

	for (g = g - 1; g >= 0; g--)
	{
		char z = str[g];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Print a string in rot13.
 * @types: Lists of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates all active flags
 * @width: gets width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char y;
	char *str;
	unsigned int g, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (g = 0; str[g]; g++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[g])
			{
				y = out[j];
				write(1, &y, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			y = str[g];
			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}
