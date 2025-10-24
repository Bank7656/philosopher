/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:58:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/20 01:30:41 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	picking_fork(t_philo *philo, t_rules *rules);
static void	eating(t_philo *philo, t_rules *rules);
static void	sleeping(t_philo *philo, t_rules *rules);
static void	release_fork(t_philo *philo, t_rules *rules);

void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo -> rules;
	while (philo -> table -> is_dining)
	{
		print_status(philo, rules, THINKING_MSG);
		picking_fork(philo, rules);
		eating(philo, rules);
		release_fork(philo, rules);
		sleeping(philo, rules);
	}
	return (NULL);
}

static void	picking_fork(t_philo *philo, t_rules *rules)
{
	if (philo -> id % 2 != 0)
	{
		pthread_mutex_lock(philo -> left_fork);
		print_status(philo, rules, PICKING_MSG);
		pthread_mutex_lock(philo -> right_fork);
		print_status(philo, rules, PICKING_MSG);
	}
	else
	{
		pthread_mutex_lock(philo -> right_fork);
		print_status(philo, rules, PICKING_MSG);
		pthread_mutex_lock(philo -> left_fork);
		print_status(philo, rules, PICKING_MSG);
	}
	return ;
}

static void	release_fork(t_philo *philo, t_rules *rules)
{
	if (philo -> id % 2 != 0)
	{
		pthread_mutex_unlock(philo -> right_fork);
		pthread_mutex_unlock(philo -> left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo -> left_fork);
		pthread_mutex_unlock(philo -> right_fork);
	}
}

static void	eating(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&philo -> data_mutex);
	print_status(philo, rules, EATING_MSG);
	philo->last_meal_time = get_time_in_ms();
    philo->eat_count++;
	pthread_mutex_unlock(&philo -> data_mutex);
	usleep(rules -> time_to_eat * 1000);
	return ;
}

static void	sleeping(t_philo *philo, t_rules *rules)
{
	print_status(philo, rules, SLEEPING_MSG);
	usleep(rules -> time_to_sleep * 1000);
	return ;
}

void	print_status(t_philo *philo, t_rules *rules, char *msg)
{
	long long	current_time;
	long long	elasped_time;

	current_time = get_time_in_ms();
	elasped_time = current_time - philo -> last_meal_time;
	printf("%lld %i %s\n", elasped_time, philo -> id, msg);	
}
