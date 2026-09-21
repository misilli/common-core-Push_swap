/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 19:54:19 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/21 11:18:51 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted(t_list *stack)
{
	while (stack && stack->next)
	{
		if (stack->content > stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static int	ft_get_maxindex(t_list *stack)
{
	int	maxindex;

	if (!stack)
		return (0);
	maxindex = stack->index;
	while (stack)
	{
		if (stack->index > maxindex)
			maxindex = stack->index;
		stack = stack->next;
	}
	return (maxindex);
}

static int	count_bits(int n)
{
	int	bits;

	bits = 0;
	while (n > 0)
	{
		bits++;
		n >>= 1;
	}
	return (bits);
}

static void	radix_pass(t_list **a, t_list **b, int bit, t_counter *counts)
{
	int	size;

	size = ft_lstsize(*a);
	while (size > 0)
	{
		if (((*a)->index >> bit) & 1)
			counts->ra_count += ra(a);
		else
			counts->pb_count += pb(a, b);
		size--;
	}
	while (*b)
		counts->pa_count += pa(a, b);
}

int	ft_complex(t_list **a, t_list **b, t_counter *counts)
{
	int	bit;
	int	bits;

	bit = 0;
	bits = count_bits(ft_get_maxindex(*a));
	while (bit < bits && !is_sorted(*a))
	{
		radix_pass(a, b, bit, counts);
		bit++;
	}
	return (1);
}
