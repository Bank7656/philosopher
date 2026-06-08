/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:28:41 by thacharo          #+#    #+#             */
/*   Updated: 2026/06/05 14:01:51 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	init_meal_sems(t_data *data);

static int	init_meal_sems(t_data *data)
{
	int		i;
	char	name[20];

	i = 0;
	while (i < data->num_philos)
	{
		ft_make_sem_name(name, i);
		sem_unlink(name);
		data->philos[i].meal_sem = sem_open(name, O_CREAT, 0644, 1);
		if (data->philos[i].meal_sem == SEM_FAILED)
			return (1);
		i++;
	}
	return (0);
}

int	init_semaphore(t_data *data)
{
	unsigned int	fork_num;

	fork_num = data->num_philos;
	sem_unlink(FORK_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
	sem_unlink(TABLE_SEM_NAME);
	data->forks_sem = sem_open(FORK_SEM_NAME, O_CREAT, 0644, fork_num);
	if (data->forks_sem == SEM_FAILED)
		return (1);
	data->print_sem = sem_open(PRINT_SEM_NAME, O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (1);
	if (init_meal_sems(data))
		return (1);
	if (fork_num < 2)
		data->table_sem = sem_open(TABLE_SEM_NAME, O_CREAT, 0644, 1);
	else
		data->table_sem = sem_open(TABLE_SEM_NAME, O_CREAT, 0644, fork_num / 2);
	if (data->table_sem == SEM_FAILED)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;
	int	n;

	n = data->num_philos;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!data->philos)
		return (EXIT_FAILURE);
	data->forks_sem = NULL;
	data->print_sem = NULL;
	data->table_sem = NULL;
	i = 0;
	while (i < n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].meal_sem = NULL;
		data->philos[i].data = data;
		i++;
	}
	return (EXIT_SUCCESS);
}
