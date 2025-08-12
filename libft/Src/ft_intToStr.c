#include "../libft.h"

void intToStr(int N, char *str)
{
    int i;
    int sign;
    int j;
    int k;

    i = 0;
    sign = N;
    if (N == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (N < 0)
        N = -N;
    while (N > 0)
    {
        str[i++] = (N % 10) + '0';
        N /= 10;
    }
    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';
    j = 0;
    k = i - 1;
    while (j < k)
        ft_swap_char(&str[j++], &str[k--]);
}
