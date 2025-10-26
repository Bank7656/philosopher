/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:05:44 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/26 14:08:28 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool    is_someone_dead(t_table *table, t_rules *rules, t_philo *philo);
static bool    is_finish(t_table *table, t_rules *rules, int all_have_eaten);
static int     check_eat_count(t_philo *philo, t_rules *rules);

void	monitor_thread(t_table *table, t_rules *rules)
{
	int			i;
	int			all_have_eaten;

	while (true)
	{
		i = 0;
		all_have_eaten = 1;
		while (i < rules -> number_of_philosophers)
		{
			pthread_mutex_lock(&table -> philosopher[i].data_mutex);
            if (is_someone_dead(table, rules, &table -> philosopher[i]))
                return ;
            all_have_eaten = check_eat_count(&table -> philosopher[i], rules);
			pthread_mutex_unlock(&table -> philosopher[i].data_mutex);
			i++;
		}
        if (is_finish(table, rules, all_have_eaten))
            return ;
		usleep(1000);
	}
}

bool is_someone_dead(t_table *table, t_rules *rules, t_philo *philo)
{
    long long	waiting_time;

    waiting_time = get_time_in_ms() - philo -> last_meal_time;
    if (waiting_time > rules -> time_to_die)
    {
        pthread_mutex_lock(&table -> dining_mutex);
        table -> is_dining = 0;
        pthread_mutex_unlock(&table -> dining_mutex);
        print_status(philo, rules, DYING_MSG);
        pthread_mutex_unlock(&philo -> data_mutex);
        return (true);
    }
    return (false);
}

static int check_eat_count(t_philo *philo, t_rules *rules)
{
    int must_eat_count;
    
    must_eat_count = rules -> number_of_times_each_philosopher_must_eat;
    if (must_eat_count > 0)
    {
    	if (philo -> eat_count < must_eat_count)
    		return (0);            
    }
    return (1); 
}

static bool is_finish(t_table *table, t_rules *rules, int all_have_eaten)
{
    if (rules -> number_of_times_each_philosopher_must_eat > 0 && all_have_eaten)
    {
        pthread_mutex_lock(&table -> dining_mutex);
        table -> is_dining = 0;
        pthread_mutex_unlock(&table -> dining_mutex);
        return (true);
    }
    return (false);
}