/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 00:57:15 by thacharo          #+#    #+#             */
/*   Updated: 2026/06/08 12:14:59 by thacharo         ###   ########.fr       */
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
		ft_usleep(philo->data->time_to_eat / 10, philo->data);
	while (!get_death_flag(philo->data))
	{
		picking_fork(philo);
		eating(philo);
		release_fork(philo);
		print_status(philo, SLEEPING_MSG);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		if (get_death_flag(philo->data))
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}

/*
** Calculates dynamic delay to synchronize threads and prevent deadlocks.
**
** Even philos: Thinks for (eat - sleep) - 5 to yield to the other half.
** Odd philos: Uses absolute timing (last_meal + ttd - 5) so each cycle
** self-corrects for drift accumulated in eating/sleeping ft_usleep calls.
** The -5ms in both branches is the pre-queue margin to enter the mutex
** wait list before neighboring forks drop.
** Even branch is capped at (die / 2) as a safety bound.
*/
static void	thinking(t_philo *philo)
{
	long long	think_time;
	long long	death_deadline;

	print_status(philo, THINKING_MSG);
	if (philo->data->num_philos % 2 == 0)
	{
		think_time = philo->data->time_to_eat - philo->data->time_to_sleep - 5;
		if (think_time > philo->data->time_to_die / 2)
			think_time = philo->data->time_to_die / 2;
	}
	else
	{
		pthread_mutex_lock(&philo->meal_lock);
		death_deadline = philo->last_meal_time + philo->data->time_to_die;
		think_time = death_deadline - 5 - get_time_in_ms();
		pthread_mutex_unlock(&philo->meal_lock);
	}
	if (think_time > 0)
		ft_usleep(think_time, philo->data);
}

static void	eating(t_philo *philo)
{
	if (get_death_flag(philo->data))
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time_in_ms() - philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return ;
	}
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, EATING_MSG);
	ft_usleep(philo->data->time_to_eat, philo->data);
}

static void	picking_fork(t_philo *philo)
{
	if (get_death_flag(philo->data))
		return ;
	if (philo->left_fork < philo->right_fork)
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
	if (philo->left_fork < philo->right_fork)
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
