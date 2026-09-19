#include <stdlib.h>
#include "push_swap.h"

static int is_valid_flag(char *flag)
{
	if (!flag)
		return (0);
	if (ft_strnstr(flag, "--bench", 7))
		return (1);
	if (ft_strnstr(flag, "--simple", 8))
		return (1);
	if (ft_strnstr(flag, "--adaptive", 10))
		return (1);
	if (ft_strnstr(flag, "--medium", 8))
		return (1);
	if (ft_strnstr(flag, "--complex", 9))
		return (1);
	return (0);
}

static int init_main_state(t_main **state)
{
	(*state) = (t_main *)malloc(sizeof(t_main));
	if (!(*state))
		return (0);
	(*state)->a = NULL;
	(*state)->b = NULL;
	(*state)->flags = (char **)malloc(sizeof(char *) * 2);
	if (!(*state)->flags)
	{
		free(*state);
		*state = NULL;
		return (0);
	}
	(*state)->flags[0] = NULL;
	(*state)->flags[1] = NULL;
	(*state)->bench = NULL;
	(*state)->algorithm = NULL;
	(*state)->fcount = 0;
	(*state)->disorder = 0.0;
	return (1);
}

static int append_number(char *token, t_main *state)
{
	int i;
	int value;
	t_list *new_node;

	if (!token || token[0] == '\0')
		return (0);
	i = 0;
	if (token[0] == '+' || token[0] == '-')
	{
		if (!token[1] || !ft_isdigit((unsigned char)token[1]))
			return (0);
		i = 1;
	}
	while (token[i])
	{
		if (!ft_isdigit((unsigned char)token[i]))
			return (0);
		i++;
	}
	value = ft_atoi(token);
	new_node = ft_lstnew(value);
	return (ft_lstadd_back(&state->a, new_node));
}

static int handle_flag_token(char *token, t_main *state)
{
	if (!is_valid_flag(token))
		return (0);
	if (ft_strnstr(token, "--bench", 7))
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

int flagkontrol(char ***temp, t_main **arguments2)
{
	int i;
	int j;

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

char ***flagbulucu(char **argv)
{
	char ***temp;
	int i;
	int argc;

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
