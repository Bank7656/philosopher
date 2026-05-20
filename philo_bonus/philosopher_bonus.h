/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:09:17 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/20 20:35:56 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# define EXIT_SUCCESS		0
# define EXIT_FAILURE		1

# define FORK_SEM_NAME		"/fork_sem"
# define PRINT_SEM_NAME		"/print_sem"
# define MEAL_SEM_NAME		"/meal_sem"
# define TABLE_SEM_NAME		"/table_sem"
# define PICKING_MSG		"has taken a fork"
# define EATING_MSG			"is eating"
# define SLEEPING_MSG		"is sleeping"
# define THINKING_MSG		"is thinking"
# define DYING_MSG			"is died"
# define ERR_INIT			"Error: Failed to initialize philosophers.\n"
# define ERR_NUM_ARGS		"Error: Invalid number of arguments.\n"
# define ERR_INVALID_ARGS	"Error: Invalid argument values provided.\n"

# include <sys/time.h>
# include <sys/wait.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread_id;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long long		start_time;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*meal_sem;
	sem_t			*table_sem;
	t_philo			*philos;
}   t_data;


int			parse_args(t_data *data, char **argv);
int			init_semaphore(t_data *data);
int			init_philos(t_data *data);
int			dining_philosopher(t_data *data);
void		clear_resource(t_data *data);
void		kill_all_child(t_data *data);
void		philosopher(t_philo *philo);
void		*monitor(void *arg);
void		print_status(t_philo *philo, char *msg);

int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
void		ft_usleep(long time_in_ms, t_data *data);
long long	get_time_in_ms(void);

#endif
