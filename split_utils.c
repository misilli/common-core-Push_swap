/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 10:59:47 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 16:05:22 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	**free_memory(char **final, int index)
{
	while (index >= 0)
	{
		free(final[index]);
		index--;
	}
	free(final);
	return (NULL);
}

static int	ft_wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return ((int)len);
}

static char	**ft_splitfill(char **final, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			k = ft_wordlen(s + i, c);
			final[j] = (char *)ft_calloc(k + 1, sizeof(char));
			if (!final[j])
				return (free_memory(final, j - 1));
			ft_strlcpy(final[j], s + i, k + 1);
			j++;
			i += k;
		}
		else
			i++;
	}
	final[j] = NULL;
	return (final);
}

char	**ft_split(char const *s, char c)
{
	char	**final;
	int		i;
	int		word;

	if (!s)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word++;
		i++;
	}
	final = (char **)ft_calloc(word + 1, sizeof(char *));
	if (!final)
		return (NULL);
	return (ft_splitfill(final, s, c));
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (size == 0)
		return (len);
	while (src[i] != '\0' && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
