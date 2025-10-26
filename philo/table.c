/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:24:52 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/20 01:17:38 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


t_table	*init_table(t_rules *rules)
{
	int		i;
	int		size;
	t_table *table;
	
	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (clear_table(table, rules));
	size = rules -> number_of_philosophers;
	table -> philosopher = (t_philo *)malloc(sizeof(t_philo) * size);
	table -> fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	if (table -> philosopher == NULL || table -> fork == NULL)
		return (clear_table(table, rules));
	
	i = 0;
	while (i < 2)
	{
		pthread_mutex_init(&table -> fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&table -> dining_mutex, NULL);
	pthread_mutex_init(&table-> print_mutex, NULL);
	table -> is_dining = 1;
	return (table);
}

void	*clear_table(t_table *table, t_rules *rules)
{
	int	i;

	if (table == NULL)
		return (NULL);
	if (table -> fork != NULL)
	{
		i = 0;
		while (i < rules -> number_of_philosophers)
		{
			pthread_mutex_destroy(&table -> fork[i]);
			i++;
		}
		free(table -> fork);
	}
	if (table -> philosopher != NULL)
	{
		i = 0;
		while (i < rules -> number_of_philosophers)
		{
			pthread_mutex_destroy(&table -> philosopher[i].data_mutex);
			i++;
		}
		free(table -> philosopher);
	}
	pthread_mutex_destroy(&table -> print_mutex);
	pthread_mutex_destroy(&table -> dining_mutex);
	free(table);
	return (NULL);
}