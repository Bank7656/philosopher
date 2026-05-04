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

struct s_data;

typedef struct s_philo 
{
	int             id;
	int             meals_eaten;
	long long       last_meal_time;
	pthread_t       thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t meal_lock;     /* Protects last_meal_time & meals_eaten */
	struct s_data   *data;         /* Pointer to global rules/state */
}	t_philo;

typedef struct s_data 
{
	int             num_philos;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             max_meals;
	int             is_dead;       /* Global kill switch */
	long long       start_time;    /* Millisecond 0 for the simulation */
	pthread_mutex_t dead_lock;     /* Protects the is_dead flag */
	pthread_mutex_t write_lock;    /* Prevents overlapping print statements */
	pthread_mutex_t *forks;        /* Array of fork mutexes */
	t_philo         *philos;       /* Array of philosopher structures */
}	t_data;

int			parse_args(t_data *data, char **argv);
int			init_mutexes(t_data *data);
int			init_fork(t_data *data);
int			dining_philosopher(t_data *data);
int			init_philos(t_data *data);
void    	*routine(void *args);
void		clear_resource(t_data *data);

void		set_death_flag(t_data *data);
int			get_death_flag(t_data *data);

int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
void		ft_usleep(long time_in_ms, t_data *data);
long long	get_time_in_ms(void);

void		print_status(t_philo *philo, char *msg);

# endif