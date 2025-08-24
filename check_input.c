/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:48:17 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/24 00:33:20 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *arg)
{
	ft_putstr(arg);
}

int	check_input(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			error("Error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_dup(char *av)
{
	int	nbr;

	nbr = ft_atoi(av);
	if (nbr < 1 || nbr > INT_MAX)
		return (0);
	return (1);
}

int	check_value(char **av, int ac)
{
	int		i;
	long	nbr;

	i = 1;
	nbr = 0;
	while (i < ac)
	{
		if (!check_dup(av[i]))
		{
			error("Error\n");
			return (0);
		}
		i++;
	}
	return (1);
}
