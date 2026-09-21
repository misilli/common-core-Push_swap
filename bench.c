/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 03:13:56 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/21 09:50:47 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	while (s && s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = n + '0';
		ft_putchar_fd(c, fd);
	}
}

char	*strategy_name(char *algorithm)
{
	if (!ft_strcmp(algorithm, "--simple"))
		return ("Simple");
	if (!ft_strcmp(algorithm, "--medium"))
		return ("Medium");
	if (!ft_strcmp(algorithm, "--complex"))
		return ("Complex");
	return ("Adaptive");
}

char	*strategy_class(char *algorithm)
{
	if (!ft_strcmp(algorithm, "--simple"))
		return ("O(n²)");
	if (!ft_strcmp(algorithm, "--medium"))
		return ("O(n√n)");
	return ("O(n log n)");
}

static void	ft_print_disorder(t_main *data)
{
	int	percent;

	percent = (int)(data->disorder * 10000.0 + 0.5);
	ft_putstr_fd("[bench] disorder:  ", 2);
	ft_putnbr_fd(percent / 100, 2);
	ft_putstr_fd(".", 2);
	if (percent % 100 < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(percent % 100, 2);
	ft_putstr_fd("%\n", 2);
}

static void	print_strategy(t_main *data)
{
	ft_putstr_fd("[bench] strategy:  ", 2);
	ft_putstr_fd(strategy_name(data->algorithm), 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(strategy_class(data->algorithm), 2);
	ft_putstr_fd("\n", 2);
}

static void	print_count(char *name, int value, char *end)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(":  ", 2);
	ft_putnbr_fd(value, 2);
	ft_putstr_fd(end, 2);
}

static void	ft_print_counts(t_main *data)
{
	t_counter	*c;

	c = data->counts;
	ft_putstr_fd("[bench] ", 2);
	print_count("sa", c->sa_count, "  ");
	print_count("sb", c->sb_count, "  ");
	print_count("ss", c->ss_count, "  ");
	print_count("pa", c->pa_count, "  ");
	print_count("pb", c->pb_count, "\n");
	ft_putstr_fd("[bench] ", 2);
	print_count("ra", c->ra_count, "  ");
	print_count("rb", c->rb_count, "  ");
	print_count("rr", c->rr_count, "  ");
	print_count("rra", c->rra_count, "  ");
	print_count("rrb", c->rrb_count, "  ");
	print_count("rrr", c->rrr_count, "\n");
}

void	ft_bench(t_main *data)
{
	t_counter	*c;
	int			total;

	c = data->counts;
	total = c->sa_count + c->sb_count + c->ss_count + c->pa_count
		+ c->pb_count + c->ra_count + c->rb_count + c->rr_count
		+ c->rra_count + c->rrb_count + c->rrr_count;
	ft_print_disorder(data);
	print_strategy(data);
	ft_putstr_fd("[bench] total_ops:  ", 2);
	ft_putnbr_fd(total, 2);
	ft_putstr_fd("\n", 2);
	ft_print_counts(data);
}
