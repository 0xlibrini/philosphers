/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:36:58 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/24 00:11:43 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	tasks(t_rules *rules, t_philo *philos)
{
	int			j;
	pthread_t	monitor;

	j = 0;
	while (j < rules->nbr_philo)
	{
		if (pthread_create(&philos[j].thread, NULL, routine, &philos[j]))
		{
			while (j--)
				pthread_join(philos[j].thread, NULL);
			ft_clean_up(rules, philos);
			return (0);
		}
		j++;
	}
	pthread_create(&monitor, NULL, check_die, philos);
	j = 0;
	while (j < rules->nbr_philo)
	{
		pthread_join(philos[j].thread, NULL);
		j++;
	}
	pthread_join(monitor, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	t_rules	*rules;

	i = 1;
	if (ac != 5 && ac != 6)
		return (error("Error in arguments\n"), 1);
	while (i < ac)
	{
		if (!check_input(av[i++]))
			return (2);
	}
	if (!check_value(av, ac))
		return (3);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (error("Error allocation memmory\n"), 4);
	memset(rules, 0, sizeof(t_rules));
	if (!initialize(rules, av))
		return (5);
	if (!init_philo(rules))
		return (6);
	free(rules->forks);
	free(rules);
}
