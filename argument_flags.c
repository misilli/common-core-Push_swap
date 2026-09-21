/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 18:43:15 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/21 10:41:29 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_valid_flag(char *flag)
{
	if (!flag)
		return (0);
	if (!ft_strcmp(flag, "--bench"))
		return (1);
	if (!ft_strcmp(flag, "--simple"))
		return (1);
	if (!ft_strcmp(flag, "--adaptive"))
		return (1);
	if (!ft_strcmp(flag, "--medium"))
		return (1);
	if (!ft_strcmp(flag, "--complex"))
		return (1);
	return (0);
}

static int	init_main_state(t_main **state)
{
	(*state) = (t_main *)ft_calloc(1, sizeof(t_main));
	if (!(*state))
		return (0);
	(*state)->flags = (char **)ft_calloc(2, sizeof(char *));
	if (!(*state)->flags)
	{
		free(*state);
		*state = NULL;
		return (0);
	}
	(*state)->counts = (t_counter *)ft_calloc(1, sizeof(t_counter));
	if (!(*state)->counts)
	{
		free((*state)->flags);
		free(*state);
		*state = NULL;
		return (0);
	}
	return (1);
}

static int	handle_flag_token(char *token, t_main *state)
{
	if (!is_valid_flag(token))
		return (0);
	if (!ft_strcmp(token, "--bench"))
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

int	flag_control(char ***temp, t_main **data)
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
		temp[i] = (char **)ft_calloc(2, sizeof(char *));
		if (!temp[i])
		{
			while (i--)
				free(temp[i]);
			free(temp);
			return (NULL);
		}
		temp[i][0] = argv[i];
		i++;
	}
	return (temp);
}
