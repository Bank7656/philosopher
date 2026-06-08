/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:29:20 by thacharo          #+#    #+#             */
/*   Updated: 2026/06/08 15:16:40 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	thinking(t_philo *philo);
static void	picking_fork(t_philo *philo);
static void	eating(t_philo *philo);

void	routine(t_philo *philo)
{
	int	n;
	int	eating_limit;

	n = philo->data->num_philos;
	eating_limit = philo->data->max_meals;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo->data);
	else if (philo->id == n && n % 2 != 0)
		ft_usleep(philo->data->time_to_eat * 1.5, philo->data);
	while (true)
	{
		picking_fork(philo);
		eating(philo);
		if (eating_limit > 0 && philo->meals_eaten >= eating_limit)
			break ;
		print_status(philo, SLEEPING_MSG);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
	}
}

static void	picking_fork(t_philo *philo)
{
	sem_wait(philo->data->table_sem);
	sem_wait(philo->data->forks_sem);
	print_status(philo, PICKING_MSG);
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die + 10, philo->data);
		sem_post(philo->data->forks_sem);
		sem_post(philo->data->table_sem);
		while (true)
			usleep(1000);
	}
	sem_wait(philo->data->forks_sem);
	print_status(philo, PICKING_MSG);
}

static void	eating(t_philo *philo)
{
	sem_wait(philo->meal_sem);
	if (get_time_in_ms() - philo->last_meal_time >= philo->data->time_to_die)
	{
		sem_post(philo->meal_sem);
		sem_post(philo->data->forks_sem);
		sem_post(philo->data->forks_sem);
		sem_post(philo->data->table_sem);
		while (true)
			usleep(1000);
	}
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	sem_post(philo->meal_sem);
	print_status(philo, EATING_MSG);
	ft_usleep(philo->data->time_to_eat, philo->data);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->table_sem);
}

static void	thinking(t_philo *philo)
{
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	think_time;

	time_to_eat = philo->data->time_to_eat;
	time_to_sleep = philo->data->time_to_sleep;
	print_status(philo, THINKING_MSG);
	if (philo->data->num_philos % 2 != 0)
	{
		think_time = (time_to_eat * 2) - time_to_sleep - 5;
		if (think_time < 0)
			think_time = 0;
		ft_usleep(think_time, philo->data);
	}
	else
	{
		think_time = time_to_eat - time_to_sleep;
		if (think_time < 0)
			think_time = 0;
		ft_usleep(think_time, philo->data);
	}
}

void	philosopher(t_philo *philo)
{
	if (pthread_create(&philo->thread_id, NULL, &monitor, philo) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(philo->thread_id);
	routine(philo);
	exit(EXIT_SUCCESS);
}
