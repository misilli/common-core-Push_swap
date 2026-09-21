/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 10:56:18 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 10:57:09 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_atob(t_list **ap, t_list **bp)
{
	t_list	*temp;

	temp = (*ap)->next;
	(*ap)->next = *bp;
	*bp = *ap;
	*ap = temp;
}

int	pa(t_list **a_st, t_list **b_st)
{
	if (!a_st || !b_st || !*b_st)
		return (0);
	ft_atob(b_st, a_st);
	ft_putstr("pa\n");
	return (1);
}

int	pb(t_list **a_st, t_list **b_st)
{
	if (!a_st || !b_st || !*a_st)
		return (0);
	ft_atob(a_st, b_st);
	ft_putstr("pb\n");
	return (1);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
