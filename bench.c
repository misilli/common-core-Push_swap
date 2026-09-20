/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 03:13:56 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/19 23:04:40 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

static void	ft_putnbr_fd(int n, int fd)
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

static char	*strategy_name(char *algorithm)
{
	if (ft_strcmp(algorithm, "--simple") == 0)
		return ("Simple");
	if (ft_strcmp(algorithm, "--medium") == 0)
		return ("Medium");
	if (ft_strcmp(algorithm, "--complex") == 0)
		return ("Complex");
	return ("Adaptive");
}

static char	*strategy_class(char *algorithm)
{
	if (ft_strcmp(algorithm, "--simple") == 0)
		return ("O(n²)");
	if (ft_strcmp(algorithm, "--medium") == 0)
		return ("O(n√n)");
	return ("O(n log n)");
}

static void	ft_print_disorder(t_main *data)
{
	int	percent;

	percent = (int)(data->disorder * 100.0);
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

static int	ft_total_ops(t_main *data)
{
	if (!data || !data->counts)
		return (0);
	return (data->counts->sa_count + data->counts->sb_count
		+ data->counts->ss_count + data->counts->pa_count
		+ data->counts->pb_count + data->counts->ra_count
		+ data->counts->rb_count + data->counts->rr_count
		+ data->counts->rra_count + data->counts->rrb_count
		+ data->counts->rrr_count);
}

static void	print_counts(t_counter *counts)
{
	ft_putstr_fd("[bench] ", 2);
	ft_putstr_fd("sa:  ", 2);
	ft_putnbr_fd(counts->sa_count, 2);
	ft_putstr_fd("  sb:  ", 2);
	ft_putnbr_fd(counts->sb_count, 2);
	ft_putstr_fd("  ss:  ", 2);
	ft_putnbr_fd(counts->ss_count, 2);
	ft_putstr_fd("  pa:  ", 2);
	ft_putnbr_fd(counts->pa_count, 2);
	ft_putstr_fd("  pb:  ", 2);
	ft_putnbr_fd(counts->pb_count, 2);
	ft_putstr_fd("\n[bench] ra:  ", 2);
	ft_putnbr_fd(counts->ra_count, 2);
	ft_putstr_fd("  rb:  ", 2);
	ft_putnbr_fd(counts->rb_count, 2);
	ft_putstr_fd("  rr:  ", 2);
	ft_putnbr_fd(counts->rr_count, 2);
	ft_putstr_fd("  rra:  ", 2);
	ft_putnbr_fd(counts->rra_count, 2);
	ft_putstr_fd("  rrb:  ", 2);
	ft_putnbr_fd(counts->rrb_count, 2);
	ft_putstr_fd("  rrr:  ", 2);
	ft_putnbr_fd(counts->rrr_count, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_bench(t_main *data)
{
	ft_print_disorder(data);
	print_strategy(data);
	ft_putstr_fd("[bench] total_ops:  ", 2);
	ft_putnbr_fd(ft_total_ops(data), 2);
	ft_putstr_fd("\n", 2);
	print_counts(data->counts);
}
