/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:25:54 by nchaknan          #+#    #+#             */
/*   Updated: 2023/06/17 11:33:24 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<stdio.h>
# include<pthread.h>
# include<unistd.h>
# include<stdlib.h>
# include<sys/time.h>

// # define NUM_PHILOSOPHERS philo->data->number_of_philos
// # define LEFT (philo->philosopher_ids - 1)
// # define RIGHT (philo->philosopher_ids) % NUM_PHILOSOPHERS

typedef struct data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				if_died;
	int				if_meals_ends;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_action;
	pthread_mutex_t	die;
	pthread_mutex_t	meals_ends;
	pthread_mutex_t	lst_meal;
	pthread_mutex_t	must_eat;
}	t_mydata;

typedef struct philo
{
	pthread_t	philosopher;
	int			philosopher_ids;
	int			left_f;
	int			right_f;
	long		time0;
	long		last_meal;
	int			number_must_eat;
	t_mydata	*data;
}	t_philos;

// Functions
void	check_args(int ac, char **av);
void	initialize(t_philos *philo, t_mydata *data, char **av);
void	my_mutex_init(t_philos *philo, t_mydata *data);
void	my_pthread_create(t_philos *philo, t_mydata *data);
void	my_pthread_join(t_philos *philo, t_mydata *data);
void	my_mutex_destroy(t_philos *philo, t_mydata *data);
void	*routine(void *arg);
void	is_eating(t_philos *philo);
void	is_sleeping(t_philos *philo);
void	is_thinking(t_philos *philo);
void	grab_forks(t_philos *philo);
void	release_forks(t_philos *philo);
void	print_action(t_philos *philo, char *str);
int		check_death(t_philos *philo, t_mydata *data);
int		check_eating_limit(t_philos *philo);
int		get_if_died(t_philos *philo);
int		get_meals_ends(t_philos *philo);
long	get_time(void);
void	my_sleep(long time);
int		ft_atoi(char *str);

#endif