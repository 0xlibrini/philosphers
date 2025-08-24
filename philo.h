/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlibrin < anlibrin@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:05:34 by anlibrin          #+#    #+#             */
/*   Updated: 2025/08/24 00:19:10 by anlibrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define INT_MAX 2147483647
# define TRUE 1

typedef struct t_rules
{
	int				nbr_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num_of_meals;
	int				time_to_thinkg;
	int				flag_died;
	int				flag_food;
	pthread_mutex_t	*forks;
	pthread_mutex_t	global;
	pthread_mutex_t	print;
	pthread_mutex_t	flag;
	pthread_mutex_t	die;
	pthread_mutex_t	food;
	long long		start;
}					t_rules;

typedef struct t_philo
{
	int				id;
	int				meals_eaten;
	int				right_fork;
	int				left_fork;
	pthread_t		thread;
	t_rules			*rule;
	pthread_mutex_t	meal;
	long long		last_meal;
}					t_philo;
long				ft_atoi(const char *nptr);
int					check_input(char *arg);
int					check_value(char **av, int ac);
int					initialize(t_rules *rules, char **av);
void				ft_putstr(char *s);
int					is_died(t_philo *philo);
void				lock_even_philo(t_philo *philo);
void				lock_odd_philo(t_philo *philo);
long long			timing(t_philo *philo);
void				ft_printf(char *s, t_philo *philo);
long long			gettime(struct timeval *time);
int					tasks(t_rules *rules, t_philo *philos);
void				*check_die(void *arg);
void				*routine(void *arg);
int					init_philo(t_rules *rules);
int					check_eaten(t_philo *philo);
long long			timing(t_philo *philo);
void				error(char *arg);
void				ft_clean_up(t_rules *rules, t_philo *philos);
int					check_eaten(t_philo *philo);
void				ft_routine(t_philo *philo);
void				ft_think(t_philo *philo);
void				ft_clean_up(t_rules *rules, t_philo *philos);
int					do_tasks(t_rules *rules, t_philo *philos);
void				ft_destroy(t_rules *rules);
void				init_ph(t_rules *rules, t_philo *philos);
void				ft_eat(t_philo *philo);
void				ft_unlock(t_philo *philo);
void				ft_sleep(t_philo *philo);
#endif