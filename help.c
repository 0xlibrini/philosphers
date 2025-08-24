/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:53:40 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/23 23:58:12 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->rule->food);
	if (philo->rule->flag_food == philo->rule->nbr_philo)
	{
		pthread_mutex_unlock(&philo->rule->food);
		return (1);
	}
	pthread_mutex_unlock(&philo->rule->food);
	return (0);
}

void	ft_routine(t_philo *philo)
{
	ft_eat(philo);
	ft_unlock(philo);
	ft_sleep(philo);
	if (is_died(philo))
		return ;
	ft_think(philo);
}

void	ft_think(t_philo *philo)
{
	if (is_died(philo))
		return ;
	ft_printf("is thinking", philo);
	usleep((philo->rule->time_to_thinkg) * 1000);
}
