/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:47:01 by thacharo          #+#    #+#             */
/*   Updated: 2026/02/20 23:51:12 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

int		check_input(char **argv);
int		check_number(char *arg);
t_data	*data_init(int argc, char **argv);
void	clear_data(t_data *data);
void	*routine(void *arg);
t_philo	*philos_init(t_data *data, int n);
int	thread_init(t_philo *philos, int n);

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	(void)philos;
	if (argc < 5 || argc > 6)
		return (1);
	if (!check_input(argv + 1))
		return (1);
	data = data_init(argc, argv);
	data -> philos = philos_init(data, data -> num_philo);
	if (thread_init(data -> philos, data -> num_philo))
		return (1);
	usleep(50000);
	clear_data(data);
	return (0);
}

int	thread_init(t_philo *philos, int n)
{
	int	i;
	pthread_t	thread_id;

	i = 0;
	while (i < n)
	{

		thread_id = (&philos[i]) -> thread_id;
		if (pthread_create(&thread_id, NULL, &routine, &philos[i]) != 0)
		{
			return (1);
		}
		if (pthread_detach(thread_id) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}



t_philo	*philos_init(t_data *data, int n)
{
	int		i;
	int		left_fork_pos;
	int		right_fork_pos;
	t_philo *philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	while (i < n)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = 0; // Need to do this
		philos[i].data = data;
		left_fork_pos = i;
		right_fork_pos = (i + 1) % n;
		philos[i].left_fork = &data -> forks[left_fork_pos];
		philos[i].right_fork = &data -> forks[right_fork_pos];
		i++;
	}
	return (philos);
}

void	*routine(void *arg)
{
	(void)arg;
	return (NULL);
}

void	clear_data(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data -> write_mutex);
	pthread_mutex_destroy(&data -> stop_mutex);
	i = 0;
	while (i < data -> num_philo)
	{
		pthread_mutex_destroy(&(data -> forks[i]));
		i++;
	}
	free(data -> philos);
	free(data -> forks);
	free(data);
}


