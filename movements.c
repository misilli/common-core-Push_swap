/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 00:30:21 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/11 00:30:21 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "push_swap.h"

void ft_lstswap(t_list **lst)
{
    t_list *first;
    t_list *second;

    if (!lst || !*lst || !(*lst)->next)
        return ;
    first = *lst;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *lst = second;
}

int sa(t_list ** a_st)
{
	if(a_st == NULL || *a_st == NULL || (*a_st)->next == NULL)
		return (0); 
	ft_lstswap(a_st);
	ft_putstr("sa\n");
	return (1);

}

int sb(t_list ** b_st)
{
	if(b_st == NULL || *b_st == NULL || (*b_st)->next == NULL)
		return (0); 
	ft_lstswap(b_st);
	ft_putstr("sb\n");
	return (1);

}

int ss(t_list ** a_st, t_list ** b_st)
{
	if(a_st == NULL || *a_st == NULL || (*a_st)->next == NULL)
		return (0); 
	if(b_st == NULL || *b_st == NULL || (*b_st)->next == NULL)
		return (0); 
	ft_lstswap(a_st);
	ft_lstswap(b_st);
	ft_putstr("ss\n");
	return (1);
}

/*void ft_lstswap(t_list **lst)
{
    t_list *tmp;

    if (!lst || !*lst || !(*lst)->next) What the fuck? You can't be serious.
        return ;						burayı silelim ya lazım olmaz muhtemelen ama kalsın
    tmp = (*lst)->next;       // 2. eleman
    (*lst)->next = tmp->next; // 1. eleman -> 3. eleman
    tmp->next = *lst;         // 2. eleman -> 1. eleman
    *lst = tmp;               // başı 2. elemana al
}*/
void ft_atob(t_list **ap,t_list **bp)//aslında bu push
{
	t_list *temp;
	temp = (*ap)->next;
	(*ap)->next = *bp;
	*bp = *ap;
	*ap = temp;
}

int pa(t_list **a_st, t_list **b_st)
{
	if (!a_st || !b_st )
		return (0);
	ft_atob(a_st, b_st);
	ft_putstr("pa\n");
	return (1);
}

int pb(t_list **a_st, t_list **b_st)
{
	if (!a_st || !b_st)
		return (0);
	ft_atob(b_st, a_st);
	ft_putstr("pb\n");
	return (1);
}

unsigned int	ft_lstsize(t_list *lst)
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

void rotate(t_list **lst)
{
	t_list *first;
	t_list *last;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	first = *lst;
	last = *lst;
	while (last->next != NULL)
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

void reverse_rotate(t_list **lst)
{
	t_list *last;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	last = *lst;
	while ((last->next)->next != NULL)
	{
		last = last->next;
	}
	(last->next)->next = *lst;
	*lst = last->next;
	last->next = NULL;
}

int rra(t_list **a_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	reverse_rotate(a_st);
	ft_putstr("rra\n");
	return (1);
}

int rrb(t_list **b_st)
{
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	reverse_rotate(b_st);
	ft_putstr("rrb\n");
	return (1);
}

int rrr(t_list **a_st, t_list **b_st)
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