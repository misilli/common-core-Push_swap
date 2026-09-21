/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 19:54:19 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/21 04:45:27 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*static int	ft_get_min(t_list *stack)
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
int   ft_get_maxindex(t_list *stack)
{
	int maxindex;
    if (!stack)
        return ;
    maxindex = stack->index;
    while (stack)
    {
        if (stack->index > maxindex)
            maxindex = stack->index;
        stack = stack->next;
    }
	return(maxindex);
}

void    ft_foundposition(t_list *stack, int target_index, int *position)
{
    *position = 0;
    while (stack)
    {
        if (stack->index == target_index)
            return ;
        (*position)++;
        stack = stack->next;
    }
}

int	complex(t_list **a, t_list **b, t_counter *counts)
{
	int minindex;
    int maxindex;
    int minposition;
    int maxposition;
    int linklength;

	minindex = 0;
    ft_get_maxindex(*a, &maxindex);
    linklength = maxindex + 1;

    ft_foundposition(*a, minindex, &minposition);
    ft_foundposition(*a, maxindex, &maxposition);
	if (linklength/2>minposition || linklength/2>maxposition)
	{
		if (minposition < maxposition)
		{
			while (minindex != (*a)->index)
				counts->ra_count += ra(a);
			counts->pb_count += pb(a, b);
			counts->rb_count += rb(b);
			minindex++;
			linklength--;
		}
		else
		{
			while (maxindex != (*a)->index)
				counts->ra_count += ra(a);
			counts->pb_count += pb(a, b);
			maxindex--;
			linklength--;
		}
		
		
	}
	else
	{
		if (minposition> maxposition)
		{
			while (minindex != (*a)->index)
				counts->rra_count += rra(a);
			counts->pb_count += pb(a, b);
			counts->rb_count += rb(b);
			minindex++;
			linklength--;

		}
		else
		{
			while (maxindex != (*a)->index)
				counts->rra_count += rra(a);
			counts->pb_count += pb(a, b);
			maxindex--;
			linklength--;
		}
		
	}
	
	
	
    

	while (*a)
	{
		min_value = ft_get_min(*a);
		while (*a && (*a)->content != min_value)
		{
			ra(a);
			counts->ra_count++;
		}
		if (*a)
		{
			pb(a, b);
			counts->pb_count++;
		}
	}
	while (*b)
	{
		pa(a, b);
		counts->pa_count++;
	}
	return (1);
}*/
int	is_sorted(t_list *stack)
{
	while (stack && stack->next)
	{
		if (stack->content > stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}
static void radix_pass(t_list **a,t_list **b, int bit, t_counter *count)
{
	int		size;

	size = ft_lstsize(*a);
	while (0 < size)
	{
		if (((*a)->index >> bit) & 1)
			count->ra_count += ra(a);
		else
			count->pb_count += pb(a, b);
		size--;
	}
	while (b)
		count->pa_count += pa(a, b);
}

int ft_complex(t_list **a, t_list **b, t_counter *count)
{
	int bit;
	int bits;

	bit = 0;
	bits = count_bits(ft_get_maxindex(*a));
	while (bit < bits && !is_sorted(*a))
	{
		radix_pass(a,b, bit, count);
		bit++;
	}
	
}