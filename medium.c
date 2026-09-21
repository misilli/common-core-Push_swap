/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:50:23 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 14:50:23 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_sqrt(int n)
{
	int	root;

	root = 0;
	while (root * root < n)
		root++;
	return (root);
}

static void	push_chunk(t_list **a, t_list **b, t_counter *counts, int hi)
{
	int	todo;
	int	mid;

	mid = ft_lstsize(*b);
	todo = hi - mid;
	mid += todo / 2;
	while (todo > 0 && *a)
	{
		if ((*a)->index < hi)
		{
			counts->pb_count += pb(a, b);
			todo--;
			if ((*b)->index < mid)
				counts->rb_count += rb(b);
		}
		else
			counts->ra_count += ra(a);
	}
}

static int	max_position(t_list *b)
{
	int	pos;
	int	best;
	int	max;

	pos = 0;
	best = 0;
	max = b->index;
	while (b)
	{
		if (b->index > max)
		{
			max = b->index;
			best = pos;
		}
		b = b->next;
		pos++;
	}
	return (best);
}

static void	pull_max(t_list **a, t_list **b, t_counter *counts)
{
	int	pos;
	int	size;

	pos = max_position(*b);
	size = ft_lstsize(*b);
	if (pos <= size / 2)
	{
		while (pos > 0)
		{
			counts->rb_count += rb(b);
			pos--;
		}
	}
	else
	{
		while (pos < size)
		{
			counts->rrb_count += rrb(b);
			pos++;
		}
	}
	counts->pa_count += pa(a, b);
}

int	ft_medium(t_list **a, t_list **b, t_counter *counts)
{
	int	chunk;
	int	hi;

	chunk = ft_sqrt(ft_lstsize(*a));
	hi = chunk;
	while (*a)
	{
		push_chunk(a, b, counts, hi);
		hi += chunk;
	}
	while (*b)
		pull_max(a, b, counts);
	return (1);
}
