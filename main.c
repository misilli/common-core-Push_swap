/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 22:09:27 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/02 22:09:27 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>




typedef struct s_list
{
	int				content;
	struct s_list	*next;
}					t_list;
void ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
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
	if (!a_st || !b_st || !*b_st)
		return (0);
	ft_atob(b_st, a_st);
	ft_putstr("pa\n");
	return (1);
}

int pb(t_list **a_st, t_list **b_st)
{
	if (!a_st || !b_st || !*a_st)
		return (0);
	ft_atob(a_st, b_st);
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



int ft_atoi(const char *str)
{
	long value;
	int i;
	int sign;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = sign * (44 - str[i]);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

t_list *ft_lstnew(int content)
{
	t_list *test;

	test = malloc(sizeof(t_list));
	if (!test)
		return (NULL);
	test->content = content;
	test->next = NULL;
	return (test);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (!lst || !new)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

int siralamacheck(t_list *a)
{

	

	while (a && a->next)
	{
		if (a->content > a->next->content)
			return (0);
		a = a->next;
	}
	return (1);
}

void simple(t_list **a, t_list **b)
{
    int i;
    int len;

    if (!a || !*a || !(*a)->next)
        return ;
	pb(a, b);
    while (*a )
    {
		
		if ((*a)->next && (*a)->content < (*a)->next->content)
            sa(a);
		
		if (*b && *a && (*b)->content < (*a)->content)
            pb(a, b);
		else
			ra(a);

        
    }
	while (*b)
            pa(a, b);
	if (!siralamacheck(*a))
		return ;
	simple(a, b);
}
int main(int argc, char ** argv)
{
	t_list *a = NULL;
	t_list *b = NULL;
	int i = 2;
	// argümanları kontrol eden fonksioynu
	if (argc < 2)
		return (1);
	a = ft_lstnew(atoi(argv[1])); // split kullan "1 2 3" şeklinde kullanıyor
	while (i < argc)
	{
		ft_lstadd_back(&a, ft_lstnew(atoi(argv[i++])));
	}
	simple(&a, &b);

	/*while (a)
	{
		if (a->next != NULL && a->content > (a->next)->content)
		{
			ft_lstswap(&a);
			printf("kosul");
		}

		ft_atob(&a, &b);
	}*/

	while (b)
	{
		printf("b stck :%d\n", b->content);
		b = b->next;
	}
	while (a)
	{
		printf("a stck :%d\n", a->content);
		a = a->next;
	}
	/*
	while (a)
	{
		printf("%d\n",a->content);
		a = a->next;
	}*/
	// freelist(a);
	// freelist(b);
}