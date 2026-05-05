/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:09:17 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 01:09:34 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define EXIT_SUCCESS		0
# define EXIT_FAILURE		1
# define SEC_TO_USEC		1000000
# define MSEC_TO_USEC		100

# define PICKING_MSG		"has taken a fork"
# define EATING_MSG			"is eating"
# define SLEEPING_MSG		"is sleeping"
# define THINKING_MSG		"is thinking"
# define DYING_MSG			"is died"
# define ERR_INIT			"Error: Failed to initialize philosophers.\n"
# define ERR_NUM_ARGS		"Error: Invalid number of arguments.\n"
# define ERR_INVALID_ARGS	"Error: Invalid argument values provided.\n"

# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				is_dead;
	long long		start_time;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int			parse_args(t_data *data, char **argv);
int			init_mutexes(t_data *data);
int			init_fork(t_data *data);
int			dining_philosopher(t_data *data);
int			init_philos(t_data *data);
void		*routine(void *args);
void		clear_resource(t_data *data);

void		set_death_flag(t_data *data);
int			get_death_flag(t_data *data);

int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
void		ft_usleep(long time_in_ms, t_data *data);
long long	get_time_in_ms(void);

void		monitor_routine(t_data *data);
void		print_status(t_philo *philo, char *msg);

#endif
