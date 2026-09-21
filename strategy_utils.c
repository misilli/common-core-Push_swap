/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 11:28:00 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 11:28:00 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
