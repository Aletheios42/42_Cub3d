/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alepinto <alepinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:40:03 by alepinto          #+#    #+#             */
/*   Updated: 2023/04/07 12:47:46 by alepinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int is_valid_base(char *base)
{
    int i, j;
    
    if (!base || !base[0] || !base[1])
        return (0);
    
    i = 0;
    while (base[i])
    {
        if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] == 127)
            return (0);
        j = i + 1;
        while (base[j])
        {
            if (base[i] == base[j])
                return (0);
            j++;
        }
        i++;
    }
    return (i);
}

static int get_digit_value(char c, char *base)
{
    int i;
    
    i = 0;
    while (base[i])
    {
        if (base[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int ft_atoi_base(char *str, char *base)
{
    int base_len;
    int result;
    int sign;
    int digit_value;
    
    base_len = is_valid_base(base);
    if (!base_len || !str)
        return (0);
    
    while (*str && (*str <= 32 || *str == 127))
        str++;
    
    sign = 1;
    while (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    
    result = 0;
    while (*str && (digit_value = get_digit_value(*str, base)) != -1)
    {
        result = result * base_len + digit_value;
        str++;
    }
    
    return (result * sign);
}
