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
		ft_usleep(philo->data->time_to_eat / 10, philo->data);
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

/*
** Calculates dynamic delay to synchronize threads and prevent deadlocks.
**
** 1. Shift Rotation (Reason: Prevents holding single forks hostage)
** - Even: Thinks for (eat - sleep) to yield to the other half of the table.
** - Odd: Thinks for (eat * 2 - sleep) to yield to BOTH neighboring shifts.
**
** 2. Drift Mitigation (Reason: Eliminates OS context-switch lag)
** - Subtracts 5ms to wake up early and wait directly in the mutex queue,
** guaranteeing instant lock acquisition the millisecond forks drop.
**
** 3. Safety Cap (Reason: Survives the strict 10ms death limit)
** - Caps sleep at (die / 2) so a thread never gets trapped in a massive
** sleep cycle and misses reporting its own starvation.
*/
static void	thinking(t_philo *philo)
{
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	think_time;

	think_time = 0;
	time_to_eat = philo->data->time_to_eat;
	time_to_sleep = philo->data->time_to_sleep;
	print_status(philo, "is thinking");
	if (philo->data->num_philos % 2 == 0)
	{
		if (time_to_eat > time_to_sleep)
			think_time = time_to_eat - time_to_sleep;
	}
	else
		think_time = (time_to_eat * 2) - time_to_sleep;
	if (think_time > 5)
		think_time -= 5;
	else
		think_time = 0;
	if (think_time > 0)
	{
		if (think_time > philo->data->time_to_die / 2)
			think_time = philo->data->time_to_die / 2;
		ft_usleep(think_time, philo->data);
	}
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
