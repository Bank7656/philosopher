/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:00:17 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 01:00:17 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, char *msg)
{
	long long	current_time;

	if (get_death_flag(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	current_time = get_time_in_ms() - philo->data->start_time;
	if (!get_death_flag(philo->data))
		printf("%lld %d %s\n", current_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
}
