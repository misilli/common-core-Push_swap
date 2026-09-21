/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   string_utils.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: azdursun <azdursun@student.42istanbul.com.tr>         +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2026/09/19 17:40:13 by azdursun                     #+#    #+#              */
/*   Updated: 2026/09/19 17:40:13 by azdursun                    ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "push_swap.h"

char *ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;
	size_t little_len;

	if (!big || !little)
		return (NULL);
	little_len = 0;
	while (little[little_len] != '\0')
		little_len++;
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (i + little_len <= len && big[i] != '\0')
	{
		j = 0;
		while (j < little_len && big[i + j] == little[j])
			j++;
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

double compute_disorder(t_list *a)
{
	double total_pairs;
	double mistakes;
	t_list *i;
	t_list *j;

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

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total;
	size_t			i;

	if (count != 0 && size > SIZE_MAX / count)
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
