/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:58:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/19 13:31:41 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	thinking(t_philosopher *philo);
static void	eating(t_philosopher *philo);
static void	sleeping(t_philosopher *philo);

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo -> table -> is_dining)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

static void	thinking(t_philosopher *philo)
{
	printf("%i %s\n", philo -> id, THINKING_MSG);	
}

static void	sleeping(t_philosopher *philo)
{
	return ;
}

static void	eating(t_philosopher *philo)
{
	return ;
}