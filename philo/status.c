/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:55:50 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/26 13:26:24 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, t_rules *rules, char *msg)
{
	int			is_dining;
	long long	current_time;
	long long	elasped_time;

    pthread_mutex_lock(&philo -> table -> dining_mutex);
    is_dining = philo -> table -> is_dining;
    if (is_dining)
    {
        pthread_mutex_lock(&philo -> table -> print_mutex);
        current_time = get_time_in_ms();
        elasped_time = current_time - philo -> table -> starting_time;
        printf("%lld %i %s\n", elasped_time, philo -> id, msg);
        pthread_mutex_unlock(&philo -> table -> print_mutex);
    }
    pthread_mutex_unlock(&philo -> table -> dining_mutex);
}

