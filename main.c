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
typedef struct s_list
{
	int             content;
	struct s_list	*next;
}					t_list;

int	ft_atoi(const char *str)
{
	long	value;
	int		i;
	int		sign;

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

t_list	*ft_lstnew(int content)
{
	t_list	*test;

	test = malloc(sizeof(t_list));
	if (!test)
		return (NULL);
	test->content = content;
	test->next = NULL;
	return (test);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
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

/*void ft_lstswap(t_list **lst)
{
    t_list *tmp;

    if (!lst || !*lst || !(*lst)->next)
        return ;
    tmp = (*lst)->next;       // 2. eleman
    (*lst)->next = tmp->next; // 1. eleman -> 3. eleman
    tmp->next = *lst;         // 2. eleman -> 1. eleman
    *lst = tmp;               // başı 2. elemana al
}*/

int main(int argc , char **argv)

{
    t_list *a;
    t_list *b;
    int i=2;

    a=ft_lstnew(atoi(argv[1]));

    while (i<argc)
    {
        ft_lstadd_back(&a,ft_lstnew(atoi(argv[i++])));
    }
	b = a;
	ft_lstswap(&a);
    while (a)
    {
        printf("%d\n",a->content);
        a = a->next;
    }
    //freelist(a);
    //freelist(b);
}