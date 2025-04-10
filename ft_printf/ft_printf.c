#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_putchar(int c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
    int len, i;

    i = 0;
    len = 0;
    while (s[i])
    {
        len += ft_putchar(s[i]);
        i++;
    }
    return (len);
}

int ft_putnbr(int n)
{
    long nb;
    int len;

    nb = n;
    len = 0;
    if (nb < 0)
    {
        len += ft_putchar('-');
        nb *= -1;
    }
    if (nb < 10)
        len += ft_putchar(nb + '0');
    else
    {
        len += ft_putnbr(nb / 10);
        len += ft_putnbr(nb % 10);
    }
    return (len);
}

int ft_puthx(unsigned int nb)
{
    char *base = "0123456789abcdef";
    int len = 0;

    if (nb >= 16)
        len += ft_puthx(nb / 16);
    len += ft_putchar(base[nb % 16]);
    return len;
}

int ft_check_print(va_list p, char c)
{
    if (c == 'c')
        return (ft_putchar(va_arg(p, int)));
    else if (c == 's')
        return (ft_putstr(va_arg(p, char *)));
    else if (c == 'd')
        return (ft_putnbr(va_arg(p, int)));
    else if (c == 'x')
        return (ft_puthx(va_arg(p, unsigned int)));
    else if (c == '%')
        return (ft_putchar('%'));
    else 
        return (ft_putchar(c));
    return 0;
}

int ft_printf(char *s, ...)
{
    int len, i;
    va_list p;

    len = 0;
    i = 0;
    va_start(p, s);
    while (s[i])
    {
        if (s[i] == '%' && !s[i + 1])
            break;
        if (s[i] == '%' && s[i + 1])
        {
            len += ft_check_print(p, s[i + 1]);
            i++;
        }
        else
            len += ft_putchar(s[i]);
        i++;
    }
    va_end(p);
    return (len);
}

int main(void)
{
    char *name = "mohammed ali";
    int age, hexnm;
    char ch = 'a';
    age = 20;
    hexnm = 42;
    ft_printf("hello my name is %s im %d my first charachter in my name is %c : %x %d\n", name, age, ch, hexnm, hexnm);
    printf("hello my name is %s im %d my first charachter in my name is %c : %x %d\n", name, age, ch, hexnm, hexnm);
}