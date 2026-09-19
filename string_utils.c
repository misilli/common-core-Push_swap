#include "push_swap.h"
#include <stddef.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
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
