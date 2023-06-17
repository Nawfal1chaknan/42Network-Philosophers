/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:54:20 by nchaknan          #+#    #+#             */
/*   Updated: 2023/06/16 19:07:22 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_action(t_philos *philo, char *str)
{
	long	a;
	int		b;

	pthread_mutex_lock(&philo->data->print_action);
	pthread_mutex_lock(&philo->data->die);
	pthread_mutex_lock(&philo->data->meals_ends);
	if (!philo->data->if_died && !philo->data->if_meals_ends)
	{
		a = get_time() - philo->time0;
		b = philo->philosopher_ids;
		printf("%ld %d %s\n", a, b, str);
	}
	pthread_mutex_unlock(&philo->data->meals_ends);
	pthread_mutex_unlock(&philo->data->die);
	pthread_mutex_unlock(&philo->data->print_action);
}

void	my_sleep(long time)
{
	long	now;

	now = get_time();
	while (1)
	{
		if (get_time() - now >= time)
			break ;
		usleep(200);
	}
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sign);
}
