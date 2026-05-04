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
	parse_args(&data, argv);
	printf("Hello Test\n");


	return (EXIT_SUCCESS);
}