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
#include "push_swap.h"

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

void simple(t_list **a, t_list **b) // simple algoritma dertleri var
{

	while (!*a)
	{
		while ((**a).content < (**b).content)
		{
			ra(a);
		}

		pb(a, b);
	}
}

int main(int argc, char **argv)

{
	t_list *a = NULL;
	t_list *b = NULL;
	int i = 2;
	// argümanları kontrol eden fonksioynu
	a = ft_lstnew(atoi(argv[1])); // split kullan "1 2 3" şeklinde kullanıyor
	while (i < argc)
	{
		ft_lstadd_back(&a, ft_lstnew(atoi(argv[i++])));
	}
	simple(&a, &b);

	while (a)
	{
		if (a->next != NULL && a->content > (a->next)->content)
		{
			ft_lstswap(&a);
			printf("kosul");
		}

		ft_atob(&a, &b);
	}

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