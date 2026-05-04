#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
        printf("Usage: ./philo philos time_die time_eat time_sleep [meals]\n");
		return (EXIT_FAILURE);
	}
	if (parse_args(&data, argv))
	{
		printf("Error: Invalid argument values provided.\n");
		return (EXIT_FAILURE);
	}
	if (init_mutexes(&data) != 0 || init_fork(&data) != 0)
	{
		printf("Error: Failed to initialize philosophers.\n");
		clear_resource(&data);
		return (EXIT_FAILURE);
	}
	if (init_philos(&data) != 0)
	{
		printf("Error: Failed to initialize philosophers.\n");
		clear_resource(&data);
		return (EXIT_FAILURE);
	}
	printf("Hello Test\n");
	return (EXIT_SUCCESS);
}

