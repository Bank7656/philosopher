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
	// monitor_routine();
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	return (EXIT_SUCCESS);
}

