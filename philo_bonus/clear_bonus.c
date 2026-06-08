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

static void	fill_int(char *buf, int n);
static void	clear_meal_sems(t_data *data);

static void	fill_int(char *buf, int n)
{
	int	len;
	int	tmp;

	len = 0;
	tmp = n;
	if (tmp == 0)
		len = 1;
	while (tmp > 0)
	{
		tmp /= 10;
		len++;
	}
	buf[len] = '\0';
	while (len > 0)
	{
		len--;
		buf[len] = '0' + (n % 10);
		n /= 10;
	}
}

void	ft_make_sem_name(char *buf, int n)
{
	char	*base;
	int		i;

	base = MEAL_SEM_BASE;
	i = 0;
	while (base[i])
	{
		buf[i] = base[i];
		i++;
	}
	fill_int(buf + i, n);
}

static void	clear_meal_sems(t_data *data)
{
	int		i;
	char	name[20];

	if (!data->philos)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meal_sem && data->philos[i].meal_sem != SEM_FAILED)
			sem_close(data->philos[i].meal_sem);
		ft_make_sem_name(name, i);
		sem_unlink(name);
		i++;
	}
}

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
	if (data->table_sem != NULL && data->table_sem != SEM_FAILED)
	{
		sem_close(data->table_sem);
		data->table_sem = NULL;
		sem_unlink(TABLE_SEM_NAME);
	}
	clear_meal_sems(data);
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
