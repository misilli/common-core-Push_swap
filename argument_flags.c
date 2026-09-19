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
#include <stdlib.h>

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

static int	is_valid_number_token(char *token)
{
	int	i;
	int	sign;
	int	value;

	if (!token || token[0] == '\0')
		return (0);
	sign = 1;
	i = 0;
	if (token[0] == '+' || token[0] == '-')
	{
		if (!token[1])
			return (0);
		sign = sign * (44 - token[i++]);
	}
	while (token[i])
	{
		if (!ft_isdigit((unsigned char)token[i]))
			return (0);
		i++;
	}
	value = ft_atoi(token);
	if ((value == 0 && sign == -1) || (sign == -1 && value > 0) || (sign == 1
			&& value < 0))
		return (0);
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
	return (ft_lstadd_back(&state->a, new_node));
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

int	flagkontrol(char ***temp, t_main **arguments2)
{
	int	i;
	int	j;

	if (!temp || !arguments2)
		return (0);
	if (!init_main_state(arguments2))
		return (0);
	i = 1;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j][0] == '-' && temp[i][j][1] == '-')
			{
				if (!handle_flag_token(temp[i][j], *arguments2))
					return (0);
			}
			else if (!append_number(temp[i][j], *arguments2))
				return (0);
			j++;
		}
		i++;
	}
	return (arguments2 && (*arguments2)->a != NULL);
}

char	***flagbulucu(char **argv)
{
	char	***temp;
	int		i;
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	temp = (char ***)malloc(sizeof(char **) * (argc + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		temp[i] = (char **)malloc(sizeof(char *) * 2);
		if (!temp[i])
			return (NULL);
		temp[i][0] = argv[i];
		temp[i][1] = NULL;
		i++;
	}
	temp[argc] = NULL;
	return (temp);
}
