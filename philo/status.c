/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 00:58:39 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 00:58:39 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

int	get_death_flag(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->dead_lock);
	status = data->is_dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (status);
}
