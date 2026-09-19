/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   rotate_moves.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: azdursun <azdursun@student.42istanbul.com.tr>         +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2026/09/19 17:40:00 by azdursun                     #+#    #+#              */
/*   Updated: 2026/09/19 17:40:00 by azdursun                    ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "push_swap.h"

void rotate(t_list **lst)
{
	t_list *first;
	t_list *last;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	first = *lst;
	last = *lst;
	while (last->next)
		last = last->next;
	*lst = first->next;
	first->next = NULL;
	last->next = first;
}

int ra(t_list **a_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	rotate(a_st);
	ft_putstr("ra\n");
	return (1);
}

int rb(t_list **b_st)
{
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	rotate(b_st);
	ft_putstr("rb\n");
	return (1);
}

int rr(t_list **a_st, t_list **b_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	rotate(a_st);
	rotate(b_st);
	ft_putstr("rr\n");
	return (1);
}
