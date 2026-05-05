/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:01:00 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 01:01:01 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_args_digit(char **argv);
static int	check_input_limits(t_data *data, char **argv);

int	parse_args(t_data *data, char **argv)
{
	if (check_args_digit(argv + 1))
		return (EXIT_FAILURE);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	data->is_dead = 0;
	if (check_input_limits(data, argv))
		return (1);
	return (0);
}

static int	check_args_digit(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_input_limits(t_data *data, char **argv)
{
	if (data->num_philos <= 0)
		return (1);
	if (data->time_to_die <= 0)
		return (1);
	if (data->time_to_eat <= 0)
		return (1);
	if (data->time_to_sleep <= 0)
		return (1);
	if (argv[5] != NULL && data->max_meals <= 0)
		return (1);
	return (0);
}
