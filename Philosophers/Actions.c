/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:13 by nchaknan          #+#    #+#             */
/*   Updated: 2023/06/17 11:36:57 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	is_eating(t_philos *philo)
{
	grab_forks(philo);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->lst_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->lst_meal);
	my_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->must_eat);
	philo->number_must_eat--;
	pthread_mutex_unlock(&philo->data->must_eat);
	release_forks(philo);
}

void	is_sleeping(t_philos *philo)
{
	print_action(philo, "is sleeping");
	my_sleep(philo->data->time_to_sleep);
}

void	is_thinking(t_philos *philo)
{
	print_action(philo, "is thinking");
}

void	grab_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_f]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->right_f]);
	print_action(philo, "has taken a fork");
}

void	release_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->left_f]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_f]);
}
