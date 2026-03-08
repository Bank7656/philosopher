/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:04:42 by thacharo          #+#    #+#             */
/*   Updated: 2026/02/20 19:53:10 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	t_data			*data;	
} t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int	ft_isdigit(int c);
int	ft_atoi(const char *nptr);

#endif