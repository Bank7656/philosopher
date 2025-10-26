/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:58:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/26 13:17:34 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_still_dining(t_table *table);
static void	picking_fork(t_philo *philo, t_rules *rules);
static void	eating(t_philo *philo, t_rules *rules);
static void	release_fork(t_philo *philo, t_rules *rules);

void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo -> rules;
	while (is_still_dining(philo -> table))
	{
		print_status(philo, rules, THINKING_MSG);
		picking_fork(philo, rules);
		eating(philo, rules);
		release_fork(philo, rules);
		print_status(philo, rules, SLEEPING_MSG);
		usleep(rules -> time_to_eat * 1000);
	}
	return (NULL);
}

static int	is_still_dining(t_table *table)
{
	int	status;
	pthread_mutex_lock(&table -> dining_mutex);
	status = table -> is_dining;
	pthread_mutex_unlock(&table -> dining_mutex);
	return (status);
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
	return ;
}

static void	eating(t_philo *philo, t_rules *rules)
{
	print_status(philo, rules, EATING_MSG);
	pthread_mutex_lock(&philo -> data_mutex);
	philo->last_meal_time = get_time_in_ms();
    philo->eat_count++;
	pthread_mutex_unlock(&philo -> data_mutex);
	usleep(rules -> time_to_sleep * 1000);
	return ;
}