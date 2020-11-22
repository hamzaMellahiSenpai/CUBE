/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 05:08:58 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 04:07:22 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static	int			wordscount(const char *s, char c)
{
	int count;
	int mot;

	count = 0;
	mot = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			mot = 0;
		else if (mot == 0)
		{
			mot = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static	int			wordlong(const char *s, int i, char c)
{
	int len;
	int j;

	len = 0;
	j = i;
	i = 0;
	while (s[j] != c && s[j])
	{
		len++;
		j++;
	}
	return (len);
}

static	void		*freememory(char **mots, int j)
{
	while (j--)
		free(mots[j]);
	free(mots);
	return (NULL);
}

static	char		**fill(const char *s, char c, char **mots)
{
	int i;
	int k;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < wordscount(s, c))
	{
		k = 0;
		while (s[i] == c && s[i])
			i++;
		mots[j] = sf_malloc(sizeof(char) * wordlong(s, i, c) + 1);
		if (mots[j] == NULL)
			return (freememory(mots, j));
		while (s[i] != c && s[i])
			mots[j][k++] = s[i++];
		mots[j][k] = '\0';
		j++;
	}
	mots[j] = 0;
	return (mots);
}

char				**ft_split(char const *s, char c)
{
	char	**mots;

	if (!s)
		return (NULL);
	mots = sf_malloc(sizeof(char *) * (wordscount(s, c) + 1));
	if (!mots)
		handle_error(Allocation_Failed, FAIL);
	return (fill(s, c, mots));
}
