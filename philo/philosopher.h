/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:46:47 by thacharo          #+#    #+#             */
/*   Updated: 2025/10/20 01:14:58 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SEC_TO_USEC 1000000
# define MSEC_TO_USEC 100
# define PICKING_MSG "has taken a fork"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define DYING_MSG "is died"

# define RED "\e[31m"
# define GREEN "\e[32m"
# define ENDCOLOR "\e[0m"

/* 
	pthread_create, pthread_detach, pthread_join
	pthread_mutex_init, pthread_mutex_destroy, 
	pthread_mutex_lock, pthread_mutex_unlock
*/
# include <stdbool.h>
# include <pthread.h>
/* printf */
# include <stdio.h>
/* malloc free */
# include <stdlib.h>
/* memset */
# include <string.h>
/* gettimeofday */
# include <sys/time.h>
/* write usleep */
# include <unistd.h>
/* INT_MAX INT_MIN */
# include <limits.h>

typedef struct s_rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
} t_rules;

// Forward-declare the t_philosopher struct
struct s_philo;

typedef struct s_table
{
	struct s_philo			*philosopher;
	pthread_mutex_t			*fork;
	pthread_mutex_t			dining_mutex;
	pthread_mutex_t			dead_mutex;
	int						is_dining;
}	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				eat_count;
	long long		last_meal_time;
	t_rules			*rules;
	t_table			*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	data_mutex;
}	t_philo;


t_table		*init_table(t_rules *rules);
void		*clear_table(t_table *table);
void		*routine(void *arg);
long long	get_time_in_ms(void);
void		print_status(t_philo *philo, t_rules *rules, char *msg);

#endif