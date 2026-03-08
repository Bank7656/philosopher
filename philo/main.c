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
t_philo	*thread_init(t_data *data);

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
	data -> philos = thread_init(data);
	usleep(50000);
	clear_data(data);
	return (0);
}

t_philo	*thread_init(t_data *data)
{
	int		n;
	int		i;
	t_philo *philos;
	pthread_t		thread_id;

	i = 0;
	n = data -> num_philo;
	philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	while (i < n)
	{
		thread_id = (&philos[i]) -> thread_id;
		if (pthread_create(&thread_id, NULL, &routine, &philos[i]) != 0)
		{
			free(philos);
			return (NULL);
		}
		if (pthread_detach(thread_id) != 0)
		{
			free(philos);
			return (NULL);
		}
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


