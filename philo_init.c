/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:05:14 by anas              #+#    #+#             */
/*   Updated: 2025/08/24 00:33:59 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr_philo)
		pthread_mutex_init(&rules->forks[i++], NULL);
	pthread_mutex_init(&rules->print, NULL);
	pthread_mutex_init(&rules->global, NULL);
	pthread_mutex_init(&rules->flag, NULL);
	pthread_mutex_init(&rules->die, NULL);
}

void	ft_destroy(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr_philo)
		pthread_mutex_destroy(&rules->forks[i++]);
	pthread_mutex_destroy(&rules->print);
	pthread_mutex_destroy(&rules->global);
	pthread_mutex_destroy(&rules->flag);
	pthread_mutex_destroy(&rules->die);
}

int	initialize(t_rules *rules, char **av)
{
	rules->nbr_philo = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		rules->num_of_meals = ft_atoi(av[5]);
	else
		rules->num_of_meals = -1;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nbr_philo);
	if (!rules->forks)
	{
		free(rules);
		error("Error in memory\n");
		return (0);
	}
	initialize_mutex(rules);
	rules->flag_died = 0;
	if (rules->nbr_philo % 2 && rules->time_to_sleep <= rules->time_to_eat)
		rules->time_to_thinkg = rules->time_to_eat;
	else
		rules->time_to_thinkg = 1;
	return (1);
}

void	init_ph(t_rules *rules, t_philo *philos)
{
	int				j;
	struct timeval	times;
	long long		time;

	j = 0;
	time = gettime(&times);
	while (j < rules->nbr_philo)
		philos[j++].last_meal = time;
	j = 0;
	while (j < rules->nbr_philo)
		philos[j++].rule = rules;
	rules->start = gettime(&times);
}

int	init_philo(t_rules *rules)
{
	int		j;
	t_philo	*philos;

	j = 0;
	philos = malloc(sizeof(t_philo) * rules->nbr_philo);
	if (!philos)
	{
		free(rules);
		return (error("Error memory allocation\n"), 0);
	}
	while (j < rules->nbr_philo)
	{
		philos[j].id = j + 1;
		philos[j].left_fork = j;
		philos[j].right_fork = (j + 1) % rules->nbr_philo;
		pthread_mutex_init(&philos[j].meal, NULL);
		j++;
	}
	j = 0;
	while (j < rules->nbr_philo)
		philos[j++].meals_eaten = 0;
	if (!do_tasks(rules, philos))
		return (0);
	return (1);
}
