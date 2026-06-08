/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:02:43 by thacharo          #+#    #+#             */
/*   Updated: 2026/06/05 23:26:08 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	all_philos_full(t_data *data);
static void	report_death(t_philo *philo);
static int	is_philo_died(t_philo *philo);

void	monitor_routine(t_data *data)
{
	int	i;

	while (true)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (is_philo_died(&data->philos[i]) == 1)
			{
				report_death(&data->philos[i]);
				return ;
			}
			i++;
		}
		if (all_philos_full(data))
		{
			set_death_flag(data);
			return ;
		}
		usleep(1000);
	}
}

static int	all_philos_full(t_data *data)
{
	int	i;

	if (data->max_meals == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (!is_philo_full(&data->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	report_death(t_philo *philo)
{
	long long	death_timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	if (get_death_flag(philo->data) == 0)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		death_timestamp = get_time_in_ms() - philo->data->start_time;
		printf("%lld %d died\n", death_timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

static int	is_philo_died(t_philo *philo)
{
	long long	time_elasped;

	if (is_philo_full(philo))
		return (0);
	pthread_mutex_lock(&philo->meal_lock);
	time_elasped = get_time_in_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_elasped >= philo->data->time_to_die)
		return (1);
	return (0);
}
