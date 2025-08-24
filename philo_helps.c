/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:52:55 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/24 00:05:15 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_even_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->rule->forks[philo->right_fork]);
	ft_printf("has taken a fork", philo);
	pthread_mutex_lock(&philo->rule->forks[philo->left_fork]);
	ft_printf("has taken a fork", philo);
}

void	lock_odd_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->rule->forks[philo->left_fork]);
	ft_printf("has taken a fork", philo);
	if (philo->rule->nbr_philo == 1)
	{
		usleep(philo->rule->time_to_die * 1000);
		if (is_died(philo))
			return ;
	}
	pthread_mutex_lock(&philo->rule->forks[philo->right_fork]);
	if (is_died(philo))
		return ;
	ft_printf("has taken a fork", philo);
}

long long	gettime(struct timeval *time)
{
	gettimeofday(time, NULL);
	return ((time->tv_sec * 1000LL) + (time->tv_usec / 1000));
}

long long	timing(t_philo *philo)
{
	struct timeval	times;

	return (gettime(&times) - philo->rule->start);
}

void	ft_printf(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->rule->print);
	if (is_died(philo))
	{
		pthread_mutex_unlock(&philo->rule->print);
		return ;
	}
	printf("%lld %d %s\n", timing(philo), philo->id, s);
	pthread_mutex_unlock(&philo->rule->print);
}
