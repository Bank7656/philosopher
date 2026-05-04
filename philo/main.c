#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf(ERR_NUM_ARGS);
		return (EXIT_FAILURE);
	}
	if (parse_args(&data, argv))
	{
		printf(ERR_INVALID_ARGS);
		return (EXIT_FAILURE);
	}
	if (init_mutexes(&data) != 0 || init_fork(&data) != 0)
	{
		printf(ERR_INIT);
		clear_resource(&data);
		return (EXIT_FAILURE);
	}
	if (init_philos(&data) != 0)
	{
		printf(ERR_INIT);
		clear_resource(&data);
		return (EXIT_FAILURE);
	}
	if (dining_philosopher(&data))
	{
		return (EXIT_FAILURE);
	}
	clear_resource(&data);
	return (EXIT_SUCCESS);
}

int	dining_philosopher(t_data *data)
{
	int			i;
	pthread_t	*thread_id;

	i = 0;
	data->start_time = get_time_in_ms();
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		thread_id = &data->philos[i].thread_id;
		if (pthread_create(thread_id, NULL, &routine, &data->philos[i]) != 0)
		{
			set_death_flag(data);
			while (--i >= 0)
				pthread_join(data->philos[i].thread_id, NULL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	monitor_routine(data);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	return (EXIT_SUCCESS);
}


void	report_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (get_death_flag(philo->data) == 0)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		printf("%lld %d is died\n", get_time_in_ms() - philo->data->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	is_philo_died(t_philo *philo)
{
	long long	time_elasped;

	pthread_mutex_lock(&philo->meal_lock);
	time_elasped = get_time_in_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_elasped >= philo->data->time_to_die)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	monitor_routine(t_data *data)
{
	int	i;

	while (true)
	{
		i = 0;
		while(i < data->num_philos)
		{
			if (is_philo_died(&data->philos[i]))
			{
				report_death(&data->philos[i]);
				return ;
			}
			i++;
		}
		ft_usleep(1000, data);
	}
}
