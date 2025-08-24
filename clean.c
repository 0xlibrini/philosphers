/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:58:56 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/24 00:11:43 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean_up(t_rules *rules, t_philo *philos)
{
	int	j;

	j = 0;
	while (j < rules->nbr_philo)
	{
		pthread_mutex_destroy(&philos[j].meal);
		j++;
	}
	ft_destroy(rules);
}

int	do_tasks(t_rules *rules, t_philo *philos)
{
	init_ph(rules, philos);
	if (!tasks(rules, philos))
	{
		ft_clean_up(rules, philos);
		free(philos);
		return (0);
	}
	ft_clean_up(rules, philos);
	free(philos);
	return (1);
}
