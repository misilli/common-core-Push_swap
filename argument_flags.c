/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 18:43:15 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/19 23:08:04 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_valid_flag(char *flag)
{
	if (!flag)
		return (0);
	if (ft_strcmp(flag, "--bench") == 0)
		return (1);
	if (ft_strcmp(flag, "--simple") == 0)
		return (1);
	if (ft_strcmp(flag, "--adaptive") == 0)
		return (1);
	if (ft_strcmp(flag, "--medium") == 0)
		return (1);
	if (ft_strcmp(flag, "--complex") == 0)
		return (1);
	return (0);
}

static int	init_main_state(t_main **data)
{
	(*data) = (t_main *)malloc(sizeof(t_main));
	if (!(*data))
		return (0);
	(*data)->a = NULL;
	(*data)->b = NULL;
	(*data)->flags = (char **)malloc(sizeof(char *) * 2);
	if (!(*data)->flags)
	{
		free(*data);
		*data = NULL;
		return (0);
	}
	(*data)->flags[0] = NULL;
	(*data)->flags[1] = NULL;
	(*data)->bench = NULL;
	(*data)->algorithm = NULL;
	(*data)->fcount = 0;
	(*data)->disorder = 0.0;
	(*data)->counts = (t_counter *)malloc(sizeof(t_counter));
	if (!(*data)->counts)
	{
		free((*data)->flags);
		free(*data);
		*data = NULL;
		return (0);
	}
	(*data)->counts->sa_count = 0;
	(*data)->counts->sb_count = 0;
	(*data)->counts->ss_count = 0;
	(*data)->counts->pa_count = 0;
	(*data)->counts->pb_count = 0;
	(*data)->counts->ra_count = 0;
	(*data)->counts->rb_count = 0;
	(*data)->counts->rr_count = 0;
	(*data)->counts->rra_count = 0;
	(*data)->counts->rrb_count = 0;
	(*data)->counts->rrr_count = 0;
	return (1);
}

//-0 da geçerli bir tam sayı:):)
static int	is_valid_number_token(char *token)
{
	long	value;
	int		sign;
	int		i;

	if (!token)
		return (0);
	i = 0;
	sign = 1;
	if (token[i] == '-')
		sign = -1;
	if (token[i] == '+' || token[i] == '-')
		i++;
	if (!token[i])
		return (0);
	value = 0;
	while (token[i])
	{
		if (!ft_isdigit(token[i]))
			return (0);
		value = value * 10 + (token[i++] - '0');
		if (value * sign > 2147483647 || value * sign < -2147483648L)
			return (0);
	}
	return (1);
}

static int	append_number(char *token, t_main *state)
{
	int		value;
	t_list	*new_node;

	if (!is_valid_number_token(token))
		return (0);
	value = ft_atoi(token);
	new_node = ft_lstnew(value);
	if (!new_node)
		return (0);
	if (!ft_lstadd_back(&state->a, new_node))
	{
		free(new_node);
		return (0);
	}
	return (1);
}

static int	handle_flag_token(char *token, t_main *state)
{
	if (!is_valid_flag(token))
		return (0);
	if (ft_strcmp(token, "--bench") == 0)
	{
		if (state->bench)
			return (0);
		state->bench = token;
		return (1);
	}
	if (state->fcount >= 1)
		return (0);
	state->flags[state->fcount] = token;
	state->fcount++;
	state->flags[state->fcount] = NULL;
	return (1);
}

int	flag_control(char ***temp, t_main **arguments2)
{
	int	i;
	int	j;

	if (!temp || !data)
		return (0);
	if (!init_main_state(data))
		return (0);
	i = 1;
	while (temp[i])
	{
		if (!temp[i][0])
			return (0);
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j][0] == '-' && temp[i][j][1] == '-')
			{
				if (!handle_flag_token(temp[i][j], *data))
					return (0);
			}
			else if (!is_valid_number_token(temp[i][j], *data))
				return (0);
			j++;
		}
		i++;
	}
	return (data && (*data)->a != NULL && !ft_has_duplicates((*data)->a));
}

char	***flag_finder(char **argv)
{
	char	***temp;
	int		i;
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	temp = (char ***)ft_calloc(argc + 1, sizeof(char **));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		temp[i] = ft_split(argv[i], ' ');
		if (!temp[i])
		{
			free_args(temp);
			return (NULL);
		}
		i++;
		temp[i] = NULL;
	}
	return (temp);
}
