/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 17:39:43 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 16:04:46 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_index(t_list *stack)
{
	t_list	*node1;
	t_list	*node2;

	node1 = stack;
	while (node1)
	{
		node1->index = 0;
		node2 = stack;
		while (node2)
		{
			if (node2->content < node1->content)
				node1->index++;
			node2 = node2->next;
		}
		node1 = node1->next;
	}
}

int	ft_set_algorithm(t_main *data)
{
	int	i;

	if (!data)
		return (0);
	data->algorithm = "--adaptive";
	i = 0;
	while (i < data->fcount)
	{
		if (!ft_strcmp(data->flags[i], "--simple")
			|| !ft_strcmp(data->flags[i], "--adaptive")
			|| !ft_strcmp(data->flags[i], "--medium")
			|| !ft_strcmp(data->flags[i], "--complex"))
		{
			data->algorithm = data->flags[i];
			return (1);
		}
		i++;
	}
	return (1);
}

int	ft_adaptive(t_main *data)
{
	if (!data)
		return (0);
	if (data->disorder < 0.2)
		return (simple(&data->a, &data->b, data->counts));
	if (data->disorder < 0.5)
		return (ft_medium(&data->a, &data->b, data->counts));
	return (ft_complex(&data->a, &data->b, data->counts));
}

int	ft_run_algorithm(t_main *data)
{
	if (!data)
		return (0);
	ft_set_algorithm(data);
	if (ft_is_sorted(data->a))
		return (1);
	if (!ft_strcmp(data->algorithm, "--simple"))
		return (simple(&data->a, &data->b, data->counts));
	if (!ft_strcmp(data->algorithm, "--medium"))
		return (ft_medium(&data->a, &data->b, data->counts));
	if (!ft_strcmp(data->algorithm, "--complex"))
		return (ft_complex(&data->a, &data->b, data->counts));
	if (!ft_strcmp(data->algorithm, "--adaptive"))
		return (ft_adaptive(data));
	return (1);
}

int	main(int argc, char **argv)
{
	char	***arguments;
	t_main	*data;

	if (argc < 2)
		return (0);
	data = NULL;
	arguments = flag_finder(argv);
	if (!arguments || !flag_control(arguments, &data))
	{
		ft_error();
		free_all(arguments, data);
		return (1);
	}
	data->disorder = compute_disorder(data->a);
	ft_index(data->a);
	ft_run_algorithm(data);
	if (data->bench && !ft_strcmp(data->bench, "--bench"))
	{
		ft_bench(data);
	}
	free_all(arguments, data);
	return (0);
}
