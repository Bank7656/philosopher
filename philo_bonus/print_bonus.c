/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:37:01 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/20 20:38:26 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	print_status(t_philo *philo, char *msg)
{
	long long	current_time;

	sem_wait(philo->data->print_sem);
	current_time = get_time_in_ms() - philo->data->start_time;
	printf("%lld %d %s\n", current_time, philo->id, msg);
	sem_post(philo->data->print_sem);
}
