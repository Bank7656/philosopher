/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:34:36 by thacharo          #+#    #+#             */
/*   Updated: 2026/06/08 13:26:36 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*monitor(void *arg)
{
	t_philo		*philo;
	long long	death_timestamp;
	long long	current_last_meal;
	long long	current_time;

	philo = (t_philo *)arg;
	while (true)
	{
		sem_wait(philo->data->meal_sem);
		current_last_meal = philo->last_meal_time;
		sem_post(philo->data->meal_sem);
		current_time = get_time_in_ms();
		if (current_time - current_last_meal > philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sem);
			death_timestamp = current_time - philo->data->start_time;
			printf("%lld %d %s\n", death_timestamp, philo->id, DYING_MSG);
			exit(EXIT_FAILURE);
		}
		usleep(1000);
	}
	return (NULL);
}
