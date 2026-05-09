/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 00:57:15 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 00:58:10 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	picking_fork(t_philo *philo);
static void	release_fork(t_philo *philo);
static void	eating(t_philo *philo);
static void	thinking(t_philo *philo);

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, PICKING_MSG);
		ft_usleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!get_death_flag(philo->data))
	{
		picking_fork(philo);
		eating(philo);
		release_fork(philo);
		print_status(philo, SLEEPING_MSG);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

static void	thinking(t_philo *philo)
{
	long long	time_to_think;

	time_to_think = philo->data->time_to_die - philo->data->time_to_eat;
	print_status(philo, THINKING_MSG);
	if (philo->data->num_philos % 2 != 0)
		ft_usleep(time_to_think, philo->data);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, EATING_MSG);
	ft_usleep(philo->data->time_to_eat, philo->data);
}

static void	picking_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo -> left_fork);
		print_status(philo, PICKING_MSG);
		pthread_mutex_lock(philo -> right_fork);
		print_status(philo, PICKING_MSG);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, PICKING_MSG);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, PICKING_MSG);
	}
	return ;
}

static void	release_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return ;
}
