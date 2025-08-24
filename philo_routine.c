/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:56:07 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/23 23:57:14 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	struct timeval	times;

	if (is_died(philo))
		return ;
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = gettime(&times);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
	if (philo->meals_eaten == philo->rule->num_of_meals)
	{
		pthread_mutex_lock(&philo->rule->food);
		philo->rule->flag_food++;
		pthread_mutex_unlock(&philo->rule->food);
	}
	if (is_died(philo))
		return ;
	ft_printf("is eating", philo);
	if (is_died(philo))
		return ;
	usleep(philo->rule->time_to_eat * 1000);
	if (is_died(philo))
		return ;
}

void	ft_sleep(t_philo *philo)
{
	if (is_died(philo))
		return ;
	ft_printf("is sleeping", philo);
	usleep(philo->rule->time_to_sleep * 1000);
}

void	ft_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rule->forks[philo->left_fork]);
	if (philo->rule->nbr_philo > 1)
		pthread_mutex_unlock(&philo->rule->forks[philo->right_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(philo->rule->time_to_eat);
	while (!is_died(philo))
	{
		if (check_eaten(philo))
			return (NULL);
		if (!(philo->id % 2))
			lock_even_philo(philo);
		else
			lock_odd_philo(philo);
		if (is_died(philo))
		{
			ft_unlock(philo);
			return (NULL);
		}
		ft_routine(philo);
	}
	return (NULL);
}
