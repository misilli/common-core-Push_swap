/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:49:59 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 16:05:41 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

double	compute_disorder(t_list *a)
{
	double	total_pairs;
	double	mistakes;
	t_list	*i;
	t_list	*j;

	total_pairs = 0.0;
	mistakes = 0.0;
	i = a;
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs += 1.0;
			if (i->content > j->content)
				mistakes += 1.0;
			j = j->next;
		}
		i = i->next;
	}
	if (total_pairs == 0.0)
		return (0.0);
	return (mistakes / total_pairs);
}

int	ft_has_duplicates(t_list *a)
{
	t_list	*i;
	t_list	*j;

	i = a;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->content == j->content)
				return (1);
			j = j->next;
		}
		i = i->next;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total;
	size_t			i;

	if (count != 0 && size > (size_t)-1 / count)
		return (NULL);
	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
