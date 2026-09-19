/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 03:13:56 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/19 17:15:03 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	int		i;

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
	if (ft_strnstr(algorithm, "--simple", 8))
		return ("Simple");
	if (ft_strnstr(algorithm, "--medium", 8))
		return ("Medium");
	if (ft_strnstr(algorithm, "--complex", 9))
		return ("Complex");
	return ("Adaptive");
}

static char	*strategy_class(char *algorithm)
{
	if (ft_strnstr(algorithm, "--simple", 8))
		return ("O(n²)");
	if (ft_strnstr(algorithm, "--medium", 8))
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

void	ft_bench(t_main *data)
{
	ft_print_disorder(data);
	print_strategy(data);
	ft_putstr_fd("[bench] total_ops:  ", 2);
	ft_putnbr_fd(total, 2);//counter
	ft_putstr_fd("\n", 2);
    ft_print_counts(data);
}