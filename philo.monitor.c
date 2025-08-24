/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:58:30 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/24 00:41:28 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_philo *philo)
{
	int	is_philo_dead;

	pthread_mutex_lock(&philo->rule->flag);
	is_philo_dead = philo->rule->flag_died;
	pthread_mutex_unlock(&philo->rule->flag);
	return (is_philo_dead);
}

void	set_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->rule->flag);
	philo->rule->flag_died = 1;
	pthread_mutex_unlock(&philo->rule->flag);
}

int	calcul_die(t_philo *philo)
{
	struct timeval	times;
	long long		time;

	pthread_mutex_lock(&philo->meal);
	time = gettime(&times) - philo->last_meal;
	pthread_mutex_unlock(&philo->meal);
	return (time);
}

void	print_die(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->rule->print);
	printf("%lld %d %s\n", timing(philos), philos[i].id, "is died");
	pthread_mutex_unlock(&philos->rule->print);
}

void	*check_die(void *arg)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (TRUE)
	{
		i = 0;
		while (i < philos->rule->nbr_philo)
		{
			if (calcul_die(&philos[i]) >= philos->rule->time_to_die)
			{
				set_flag(philos);
				break ;
			}
			if (check_eaten(&philos[i]))
				return (NULL);
			i++;
		}
		if (is_died(philos))
		{
			print_die(philos, i);
			return (NULL);
		}
	}
	return (NULL);
}
