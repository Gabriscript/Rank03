#include<unistd.h>
#include<stdarg.h>

int putn( long n, int base)
{
    char *x ="0123456789abcdef";
    int count = 0;

    if  (n < 0 && base == 10)
    {
        count += write(1,"-",1 );
        n = -n;
    }
    if (n >= base)
        count += putn(n/base,base);
    count += write(1, &x[n % base], 1 );
    return count;
}

int put_s(const char *s)
{
    int count = 0;
    if(!s)
        s = "(null)";
    while(*s) 
        count += write(1,s++,1);
    return count;
}

int ft_printf(const char *s, ...)
{
    int count = 0;
    int i = 0;

    va_list va;

    va_start(va, s);
    while (s[i])
   {
    if (s[i] == '%' && s[i + 1])
    {
        i++;
        if (s[i] == 'd')
            count += (long)putn(va_arg(va,int),10);
        else if (s[i] == 'x')
            count += (long)putn(va_arg(va,unsigned int),16);
        else if (s[i] == 's')
            count += put_s(va_arg(va,char *));
    }
    else
        count += write(1, &s[i], 1);
    i++;
   }
    va_end(va);
    return count;
}
