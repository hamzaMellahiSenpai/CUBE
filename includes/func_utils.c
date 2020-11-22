/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:35:21 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/03 04:37:09 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] == '\t' || str[i] == '\r' || str[i] == ' ')
			|| (str[i] == '\v' || str[i] == '\n' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res * 10 > 9223372036854775807)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		res = res * 10 + (str[i++] - '0');
	}
	return (res * sign);
}

void	*ft_memset(void *p, int val, size_t size)
{
	unsigned char *tab;

	tab = p;
	while (size--)
		*tab++ = (unsigned char)val;
	return (p);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
		if (*s1++ != *s2++)
			return (*(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1));
	return (0);
}

int		numofdigits(int n)
{
	int c;

	if (n == 0)
		return (1);
	c = 0;
	while (n)
	{
		c++;
		n /= 10;
	}
	return (c);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	while (len > 0)
	{
		*d = *s;
		d++;
		s++;
		len--;
	}
	return (dst);
}
