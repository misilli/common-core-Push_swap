/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 01:30:00 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 09:50:39 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_list **stack)
{
	t_list	*tmp;

	if (!stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

void	free_args(char ***args)
{
	int	i;
	int	j;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			free(args[i][j++]);
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_all(char ***args, t_main *data)
{
	if (data)
	{
		free_stack(&data->a);
		free_stack(&data->b);
		free(data->flags);
		free(data->counts);
		free(data);
	}
	free_args(args);
}
