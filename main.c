#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"

void ft_index(t_list *stack)
{
	t_list *node1;
	t_list *node2;

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

int ft_set_algorithm(t_main *arguments2)
{
	int i;

	if (!arguments2)
		return (0);
	arguments2->algorithm = "--adaptive";
	i = 0;
	while (i < arguments2->fcount)
	{
		if (ft_strnstr(arguments2->flags[i], "--simple", 8))
		{
			arguments2->algorithm = arguments2->flags[i];
			return (1);
		}
		if (ft_strnstr(arguments2->flags[i], "--adaptive", 10))
		{
			arguments2->algorithm = arguments2->flags[i];
			return (1);
		}
		if (ft_strnstr(arguments2->flags[i], "--medium", 8))
		{
			arguments2->algorithm = arguments2->flags[i];
			return (1);
		}
		if (ft_strnstr(arguments2->flags[i], "--complex", 9))
		{
			arguments2->algorithm = arguments2->flags[i];
			return (1);
		}
		i++;
	}
	return (1);
}

int ft_adaptive(t_main *arguments2)
{
	if (!arguments2)
		return (0);
	if (arguments2->disorder < 0.2)
		return (simple(&arguments2->a, &arguments2->b, arguments2->counts));
	return (1);
}

int ft_run_algorithm(t_main *arguments2)
{
	if (!arguments2)
		return (0);
	ft_set_algorithm(arguments2);
	if (ft_strnstr(arguments2->algorithm, "--simple", 8))
		return (simple(&arguments2->a, &arguments2->b, arguments2->counts));
	if (ft_strnstr(arguments2->algorithm, "--medium", 8))
		return (1);
	if (ft_strnstr(arguments2->algorithm, "--complex", 9))
		return (1);
	if (ft_strnstr(arguments2->algorithm, "--adaptive", 10))
		return (ft_adaptive(arguments2));
	return (1);
}

int main(int argc, char **argv)
{
	char	***arguments;
	t_main	*data;

	if (argc < 2)
		return (0);
	arguments = flagbulucu(argv);
	if (!arguments || !flagkontrol(arguments, &data))
	{
		ft_error();
		return (1);
	}
	data->disorder = compute_disorder(data->a);
	printf("Disorder: %.2f\n", data->disorder);
	ft_index(data->a);
	ft_run_algorithm(data);
	if (data->bench && ft_strnstr(data->bench, "--bench", 7))
	{
		ft_bench(data);
	}
	return (0);
}
