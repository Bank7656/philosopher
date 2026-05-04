#include "philosopher.h"
#include <string.h>

int	check_number(char *arg);

int	check_input(char **argv)
{
	char	**ptr;

	ptr = argv;
	while (*ptr != NULL)
	{
		if (!check_number(*ptr))
			return (0);
		ptr++;
	}
	return (1);
}

int	check_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

t_data	*data_init(int argc, char **argv)
{
	int		i;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data -> num_philo = ft_atoi(argv[1]);
	data -> time_to_die = ft_atoi(argv[2]);
	data -> time_to_eat = ft_atoi(argv[3]);
	data -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data -> must_eat_count = ft_atoi(argv[5]);
	else
		data -> must_eat_count = -1;
	data -> is_dining = 1;
	data -> forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (data -> num_philo));
	if (!data -> forks)
	{
		free(data);
		return (NULL);
	}

	i = 0;
	while (i < data -> num_philo)
	{
		if (pthread_mutex_init(&(data -> forks[i]), NULL) == -1)
		{
			free(data -> forks);
			free(data);
		}
		i++;
	}
	pthread_mutex_init(&data -> write_mutex, NULL);
	pthread_mutex_init(&data -> stop_mutex, NULL);
	data -> philos = NULL;
	
	// Debug
	printf("Number of philosophers: %i\n", data -> num_philo);
	printf("Time to die: %i\n", data -> time_to_die);
	printf("Time to eat: %i\n", data -> time_to_eat);
	printf("Time to sleep: %i\n", data -> time_to_sleep);
	if (argc == 6)
		printf("number_of_times_each_philosopher_must_eat: %i\n", data -> must_eat_count);
	// End debug

	return (data);
}