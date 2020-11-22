/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:26:00 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/27 23:34:22 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int			tablen(void **tab)
{
	int i;

	i = 0;
	while (*tab++)
		i++;
	return (i);
}

int			ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char		*trim(char const *s, char const *set)
{
	int				debut;
	int				fin;
	int				i;
	char			*p;

	debut = -1;
	if (!s)
		return (NULL);
	if (!set)
		return (ft_strdup(s));
	fin = ft_strlen(s);
	while (s[++debut] && ft_strchr(set, s[debut]))
		;
	while (debut < fin - 1)
		if (!ft_strchr(set, s[fin - 1]))
			break ;
		else
			fin--;
	if (!(p = sf_malloc(fin - debut + 1)))
		return (NULL);
	i = -1;
	while (++i < (fin - debut))
		p[i] = s[debut + i];
	p[i] = '\0';
	return (p);
}

int			len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	str = (char*)sf_malloc(sizeof(char) * (i + 1));
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}
