/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:49:20 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/26 13:34:18 by thacharo         ###   ########.fr       */
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


int	init_philosopher(t_table *table, t_rules *rules)
{
	int				i;
	int				left_fork_pos;
	int				right_fork_pos;
	t_philo			*philo;

	i = 0;
	philo = table -> philosopher;
	while (i < rules -> number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].last_meal_time = get_time_in_ms();
		philo[i].rules = rules;
		philo[i].table = table;
		left_fork_pos = i;
		right_fork_pos = (i + 1) % rules -> number_of_philosophers;
		philo[i].left_fork = &table -> fork[left_fork_pos];
		philo[i].right_fork = &table -> fork[right_fork_pos];
		if (pthread_mutex_init(&philo[i].data_mutex, NULL) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_thread(t_philo *philo, t_rules *rules)
{
	int			i;
	pthread_t	*thread_id;

	i = 0;
	while (i < rules -> number_of_philosophers)
	{
		thread_id = &philo[i].thread_id;
		if (pthread_create(thread_id, NULL, &routine, &philo[i]) == -1)
		{
			return (-1);
		}
		i++;
	}	
	return (0);
}

int	wait_thread(t_philo *philo, t_rules *rules)
{
	int			i;

	i = 0;
	while (i < rules -> number_of_philosophers)
	{
		if (pthread_join(philo[i].thread_id, NULL) == -1)
			return (-1);
		i++;
	}	
	return (0);
}

void	init_rules(t_rules *rules, int argc, char **argv)
{
	rules -> number_of_philosophers = 5;
	rules -> time_to_die = 800;
	rules -> time_to_eat = 200;
	rules -> time_to_sleep = 200;
	if (argc == 5)
		rules -> number_of_times_each_philosopher_must_eat = 0;
	else
		rules -> number_of_times_each_philosopher_must_eat = -1;
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
	table -> starting_time =  get_time_in_ms();
	init_philosopher(table, &rules);
	if (init_thread(table -> philosopher, &rules) == -1)
	{
		clear_table(table, &rules);
		return (EXIT_FAILURE);
	}
	monitor_thread(table, &rules);
	if (wait_thread(table -> philosopher, &rules) == -1)	
	{
		clear_table(table, &rules);
		return (EXIT_FAILURE);
	}
	clear_table(table, &rules);
	return (EXIT_SUCCESS);
}
