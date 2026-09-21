/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 10:59:13 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 10:59:31 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_get_min(t_list *stack)
{
	int	min;

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

int	simple(t_list **a, t_list **b, t_counter *counts)
{
	int	min_value;

	while (*a)
	{
		min_value = ft_get_min(*a);
		while (*a && (*a)->content != min_value)
			counts->ra_count += ra(a);
		if (*a)
			counts->pb_count += pb(a, b);
	}
	while (*b)
		counts->pa_count += pa(a, b);
	return (1);
}
