/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:38:41 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/20 20:39:44 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	wait_all_child(t_data *data);

int	main(int argc, char *argv[])
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
	if (init_philos(&data) || init_semaphore(&data))
	{
		printf(ERR_INIT);
		clear_resource(&data);
		return (EXIT_FAILURE);
	}
	if (dining_philosopher(&data))
	{
		clear_resource(&data);
		return (EXIT_FAILURE);
	}
	wait_all_child(&data);
	return (EXIT_SUCCESS);
}

int	dining_philosopher(t_data *data)
{
	int		i;
	int		j;
	t_philo	*philos;

	i = -1;
	j = -1;
	philos = data->philos;
	data->start_time = get_time_in_ms();
	while (++i < data->num_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
		{
			while (++j < i)
				kill(philos[j].pid, SIGKILL);
			return (EXIT_FAILURE);
		}
		if (philos[i].pid == 0)
		{
			philos[i].last_meal_time = get_time_in_ms();
			philosopher(&philos[i]);
			exit(EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

void	wait_all_child(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_all_child(data);
				break ;
			}
		}
		i++;
	}
	clear_resource(data);
}
