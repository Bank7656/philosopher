/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:49:20 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/19 13:51:19 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void	init_philosopher(t_table *table, t_rules *rules)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = table -> philosopher;
	while (i < 2)
	{
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].last_meal_time = get_time_in_ms();
		philo[i].table = table;
		philo[i].left_fork = &table -> fork[i];
		philo[i].right_fork = &table -> fork[(i + 1) % rules -> number_of_philosophers];
		i++;
	}
}

int	init_thread(t_philosopher *philo, t_rules *rules)
{
	int			i;
	pthread_t	*thread_id;

	i = 0;
	while (i < 2)
	{
		thread_id = &philo[i].thread_id;
		if (pthread_create(thread_id, NULL, &routine, &philo[i]) == -1)
		{
			return (-1);
		}
		i++;
	}	
	philo -> rules = rules;
	return (0);
}

int	wait_thread(t_philosopher *philo)
{
	int			i;

	i = 0;
	while (i < 2)
	{
		if (pthread_join(philo[i].thread_id, NULL) == -1)
			return (-1);
		i++;
	}	
	return (0);
}

void	init_rules(t_rules *rules, int argc, char **argv)
{
	rules -> number_of_philosophers = 2;
	rules -> time_to_die = 0;
	rules -> time_to_eat = 0;
	rules -> time_to_sleep = 0;
	rules -> number_of_times_each_philosopher_must_eat = 0;
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_table	*table;

	// parser();
	init_rules(&rules, argc, argv);
	table = init_table(&rules);
	if (table == NULL)
		return (EXIT_FAILURE);
	init_philosopher(table, &rules);
	if (init_thread(table -> philosopher, &rules) == -1)
	{
		clear_table(table);
		return (EXIT_FAILURE);
	}

	if (wait_thread(table -> philosopher) == -1)	
	{
		clear_table(table);
		return (EXIT_FAILURE);
	}
	clear_table(table);
	
	return (EXIT_SUCCESS);
}
