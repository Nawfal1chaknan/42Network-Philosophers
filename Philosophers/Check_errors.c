/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:23:08 by nchaknan          #+#    #+#             */
/*   Updated: 2023/06/17 11:28:38 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	my_exit(void)
{
	printf("Error\n");
	exit(1);
}

void	check_args(int ac, char **av)
{
	int	j;
	int	i;

	if (ac != 5 && ac != 6)
		my_exit();
	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			if (av[j][0] == '-')
				my_exit();
			else if (av[j][i] < '0' || av[j][i] > '9')
				my_exit();
			i++;
		}
		j++;
	}
}
