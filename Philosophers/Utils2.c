/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:26:20 by nchaknan          #+#    #+#             */
/*   Updated: 2023/06/17 11:37:49 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_death(t_philos *philo, t_mydata *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_lock(&philo->data->lst_meal);
		if (get_time() - philo[i].last_meal >= data->time_to_die)
		{
			print_action(&philo[i], "died");
			if (data->number_of_philos == 1)
				pthread_mutex_unlock(&philo->data->fork[philo->left_f]);
			pthread_mutex_lock(&philo->data->die);
			data->if_died = 1;
			pthread_mutex_unlock(&philo->data->die);
			pthread_mutex_unlock(&philo->data->lst_meal);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->lst_meal);
		i++;
	}
	return (0);
}

int	check_eating_limit(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->number_of_philos)
	{
		pthread_mutex_lock(&philo->data->must_eat);
		if (philo[i].number_must_eat > 0)
		{
			pthread_mutex_unlock(&philo->data->must_eat);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->must_eat);
		i++;
	}
	pthread_mutex_lock(&philo->data->meals_ends);
	philo->data->if_meals_ends = 1;
	pthread_mutex_unlock(&philo->data->meals_ends);
	return (1);
}

int	get_if_died(t_philos *philo)
{
	int	tmp;

	pthread_mutex_lock(&philo->data->die);
	tmp = philo->data->if_died;
	pthread_mutex_unlock(&philo->data->die);
	return (tmp);
}

int	get_meals_ends(t_philos *philo)
{
	int	tmp;

	pthread_mutex_lock(&philo->data->meals_ends);
	tmp = philo->data->if_meals_ends;
	pthread_mutex_unlock(&philo->data->meals_ends);
	return (tmp);
}
