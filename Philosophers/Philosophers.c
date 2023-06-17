/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:25:34 by nchaknan          #+#    #+#             */
/*   Updated: 2023/06/17 11:23:59 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->philosopher_ids % 2 == 0)
	{
		print_action(philo, "is thinking");
		usleep(100);
	}
	while (!get_if_died(philo) && !get_meals_ends(philo))
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philos	*philo;
	t_mydata	*data;

	check_args(ac, av);
	philo = malloc(sizeof(t_philos) * ft_atoi(av[1]));
	data = malloc(sizeof(t_mydata));
	data->fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	initialize(philo, data, av);
	my_mutex_init(philo, data);
	my_pthread_create(philo, data);
	while (!data->if_died && !data->if_meals_ends)
	{
		if (check_death(philo, data))
			break ;
		if (av[5])
			if (check_eating_limit(philo))
				break ;
	}
	my_pthread_join(philo, data);
	my_mutex_destroy(philo, data);
}
