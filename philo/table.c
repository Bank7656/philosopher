/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:24:52 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/19 13:23:32 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


t_table	*init_table(t_rules *rules)
{
	int		i;
	t_table *table;
	
	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (clear_table(table));
	table -> philosopher = (t_philosopher *)malloc(sizeof(t_philosopher) * rules -> number_of_philosophers);
	table -> fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * rules -> number_of_philosophers);
	if (table -> philosopher == NULL || table -> fork == NULL)
		return (clear_table(table));
	
	i = 0;
	while (i < 2)
	{
		pthread_mutex_init(&table -> fork[i], NULL);
		i++;
	}
	table -> is_dining = 1;
	return (table);
}

void	*clear_table(t_table *table)
{
	int	i;

	if (table == NULL)
		return (NULL);
	if (table -> fork != NULL)
	{
		i = 0;
		while (i < 2)
		{
			pthread_mutex_destroy(&table -> fork[i]);
			i++;
		}
		free(table -> fork);
	}
	if (table -> philosopher != NULL)
	{

		free(table -> philosopher);
	}
	
	free(table);
	return (NULL);
}