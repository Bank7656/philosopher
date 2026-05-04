#include "philosopher.h"

static void	picking_fork(t_philo *philo);
static void	release_fork(t_philo *philo);

void    *routine(void *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    while (!get_death_flag(philo->data))
    {
        picking_fork(philo);
        print_status(philo, EATING_MSG);
        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal_time = get_time_in_ms();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->meal_lock);
        ft_usleep(philo->data->time_to_eat, philo->data);
        release_fork(philo);
        print_status(philo, SLEEPING_MSG);
        ft_usleep(philo->data->time_to_sleep, philo->data);
        print_status(philo, THINKING_MSG);
    }
    return (NULL);
}

static void	picking_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo -> left_fork);
		print_status(philo, PICKING_MSG);
		pthread_mutex_lock(philo -> right_fork);
		print_status(philo, PICKING_MSG);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, PICKING_MSG);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, PICKING_MSG);
	}
	return ;
}

static void	release_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return ;
}
