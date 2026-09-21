/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 10:59:13 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 16:12:48 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_min_position(t_list *stack)
{
	int	pos;
	int	best;
	int	min;

	pos = 0;
	best = 0;
	min = stack->content;
	while (stack)
	{
		if (stack->content < min)
		{
			min = stack->content;
			best = pos;
		}
		stack = stack->next;
		pos++;
	}
	return (best);
}

static void	bring_to_top(t_list **a, int pos, t_counter *counts)
{
	int	size;

	size = ft_lstsize(*a);
	if (pos <= size / 2)
	{
		while (pos > 0)
		{
			counts->ra_count += ra(a);
			pos--;
		}
	}
	else
	{
		while (pos < size)
		{
			counts->rra_count += rra(a);
			pos++;
		}
	}
}

int	simple(t_list **a, t_list **b, t_counter *counts)
{
	while (*a)
	{
		bring_to_top(a, ft_min_position(*a), counts);
		counts->pb_count += pb(a, b);
	}
	while (*b)
		counts->pa_count += pa(a, b);
	return (1);
}
