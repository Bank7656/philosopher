/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:03:29 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 01:03:30 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_lock, NULL) == -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->dead_lock, NULL) == -1)
	{
		pthread_mutex_destroy(&data->write_lock);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_fork(t_data *data)
{
	int	i;
	int	n;

	n = data->num_philos;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!data->forks)
		return (EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i--;
			}
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_philos(t_data *data)
{
	int	i;
	int	n;

	n = data->num_philos;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!data->philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = get_time_in_ms();
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (EXIT_FAILURE);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % n];
		i++;
	}
	return (EXIT_SUCCESS);
}
