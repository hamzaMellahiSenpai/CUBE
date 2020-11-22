/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 08:21:56 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/22 04:52:13 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int			ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*ft_strdup(const char *str)
{
	int		len;
	char	*dest;

	len = ft_strlen(str);
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	dest[len] = 0;
	while (len--)
		dest[len] = ((char*)str)[len];
	return (dest);
}

char		*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c && *str)
		str++;
	if (*str != c)
		return (0);
	return (str);
}

char		*ft_strjoin(char const *s1, char const *s2, int index)
{
	int		i;
	int		k;
	char	*s12;

	k = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(s12 = sf_malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)))
		return (NULL);
	while (s1[i])
	{
		s12[i] = s1[i];
		i++;
	}
	while (s2[k])
		s12[i++] = s2[k++];
	if (index == 0)
		free_space((char**)(&s1));
	else if (index == 1)
		free_space((char**)(&s2));
	s12[i] = 0;
	return (s12);
}

char		*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 1;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest + i);
}
