#include "push_swap.h"

static int ft_get_min(t_list *stack)
{
	int min;

	if (!stack)
		return (0);
	min = stack->content;
	while (stack)
	{
		if (stack->content < min)
			min = stack->content;
		stack = stack->next;
	}
	return (min);
}

int simple(t_list **a, t_list **b, t_counter *counts)
{
	int min_value;

	while (*a)
	{
		min_value = ft_get_min(*a);
		while (*a && (*a)->content != min_value)
			ra(a);
		if (*a)
			pb(a, b);
	}
	while (*b)
		pa(a, b);
	return (1);
}
