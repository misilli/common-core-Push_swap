/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 10:57:34 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 16:05:11 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_list **lst)
{
	t_list	*last;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	last = *lst;
	while (last->next && last->next->next)
		last = last->next;
	last->next->next = *lst;
	*lst = last->next;
	last->next = NULL;
}

int	rra(t_list **a_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	reverse_rotate(a_st);
	ft_putstr("rra\n");
	return (1);
}

int	rrb(t_list **b_st)
{
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	reverse_rotate(b_st);
	ft_putstr("rrb\n");
	return (1);
}

int	rrr(t_list **a_st, t_list **b_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	reverse_rotate(a_st);
	reverse_rotate(b_st);
	ft_putstr("rrr\n");
	return (1);
}
