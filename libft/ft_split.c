/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_getword(const char *s, char c, size_t *pos)
{
	char	*word;
	size_t	len;
	size_t	i;

	while (s[*pos] == c)
		(*pos)++;
	len = 0;
	while (s[*pos + len] && s[*pos + len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[*pos + i];
		i++;
	}
	word[i] = '\0';
	*pos += len;
	return (word);
}

static void	ft_free_split(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		n;
	int		i;
	size_t	pos;

	if (!s)
		return (NULL);
	n = ft_wordcount(s, c);
	result = ft_calloc(n + 1, sizeof(char *));
	if (!result)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < n)
	{
		result[i] = ft_getword(s, c, &pos);
		if (!result[i])
		{
			ft_free_split(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
