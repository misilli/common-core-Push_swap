#include "push_swap.h"
#include <stdlib.h>

int ft_atoi(const char *str)
{
	long value;
	int i;
	int sign;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(value * sign));
}

t_list *ft_lstnew(int content)
{
	t_list *new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->index = 0;
	new_node->next = NULL;
	return (new_node);
}

int ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list *tmp;

	if (!lst || !new_node)
		return (0);
	tmp = *lst;
	while (tmp)
	{
		if (tmp->content == new_node->content)
			return (0);
		tmp = tmp->next;
	}
	if (*lst == NULL)
	{
		*lst = new_node;
		return (1);
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	return (1);
}
