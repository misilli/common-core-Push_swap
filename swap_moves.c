/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 11:01:42 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 11:02:12 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_lstswap(t_list **lst)
{
	t_list	*first;
	t_list	*second;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	first = *lst;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*lst = second;
}

int	sa(t_list **a_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	ft_lstswap(a_st);
	ft_putstr("sa\n");
	return (1);
}

int	sb(t_list **b_st)
{
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	ft_lstswap(b_st);
	ft_putstr("sb\n");
	return (1);
}

int	ss(t_list **a_st, t_list **b_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	ft_lstswap(a_st);
	ft_lstswap(b_st);
	ft_putstr("ss\n");
	return (1);
}
