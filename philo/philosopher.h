#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# include <sys/time.h>
# include <limits.h>
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

int parse_args(t_data *data, char **argv);

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);

# endif