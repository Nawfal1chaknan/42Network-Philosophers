/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pthread_and_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:36:03 by nchaknan          #+#    #+#             */
/*   Updated: 2023/06/17 11:34:28 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	initialize(t_philos *philo, t_mydata *data, char **av)
{
	int	i;

	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->if_died = 0;
	data->if_meals_ends = 0;
	i = 0;
	while (i < data->number_of_philos)
	{
		philo[i].data = data;
		philo[i].philosopher_ids = i + 1;
		philo[i].left_f = i;
		philo[i].right_f = (i + 1) % data->number_of_philos;
		philo[i].time0 = get_time();
		philo[i].last_meal = get_time();
		philo[i].number_must_eat = -1;
		if (av[5])
			philo[i].number_must_eat = ft_atoi(av[5]);
		i++;
	}
}

void	my_mutex_init(t_philos *philo, t_mydata *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philo->data->print_action, NULL);
	pthread_mutex_init(&philo->data->die, NULL);
	pthread_mutex_init(&philo->data->meals_ends, NULL);
	pthread_mutex_init(&philo->data->lst_meal, NULL);
	pthread_mutex_init(&philo->data->must_eat, NULL);
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&philo->data->fork[i], NULL);
		i++;
	}
}

void	my_pthread_create(t_philos *philo, t_mydata *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_create(&philo[i].philosopher, NULL, routine, &philo[i]);
		i++;
	}
}

void	my_pthread_join(t_philos *philo, t_mydata *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_join(philo[i].philosopher, NULL);
		i++;
	}
}

void	my_mutex_destroy(t_philos *philo, t_mydata *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_destroy(&philo->data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->print_action);
	pthread_mutex_destroy(&philo->data->die);
	pthread_mutex_destroy(&philo->data->meals_ends);
	pthread_mutex_destroy(&philo->data->lst_meal);
	pthread_mutex_destroy(&philo->data->must_eat);
}
