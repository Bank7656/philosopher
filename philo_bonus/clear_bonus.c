/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:28:04 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/20 20:28:36 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	clear_resource(t_data *data)
{
	if (data->forks_sem != NULL && data->forks_sem != SEM_FAILED)
	{
		sem_close(data->forks_sem);
		data->forks_sem = NULL;
		sem_unlink(FORK_SEM_NAME);
	}
	if (data->print_sem != NULL && data->print_sem != SEM_FAILED)
	{
		sem_close(data->print_sem);
		data->print_sem = NULL;
		sem_unlink(PRINT_SEM_NAME);
	}
	if (data->meal_sem != NULL && data->meal_sem != SEM_FAILED)
	{
		sem_close(data->meal_sem);
		data->meal_sem = NULL;
		sem_unlink(MEAL_SEM_NAME);
	}
	if (data->table_sem != NULL && data->table_sem != SEM_FAILED)
	{
		sem_close(data->table_sem);
		data->table_sem = NULL;
		sem_unlink(TABLE_SEM_NAME);
	}
}

void	kill_all_child(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}
