#include "philosopher_bonus.h"

static void	thinking(t_philo *philo);

void    *monitor(void *arg)
{
    t_philo     *philo;
    long long   death_timestamp;
    long long   current_last_meal;
    int         current_meal;
    long long   current_time;

    philo = (t_philo *)arg;
    while (true)
    {
        sem_wait(philo->data->meal_sem);
        current_last_meal = philo->last_meal_time;
        current_meal = philo->meals_eaten;
        sem_post(philo->data->meal_sem);
        current_time = get_time_in_ms();
        if (current_time - current_last_meal > philo->data->time_to_die)
        {
            sem_wait(philo->data->print_sem);
		    death_timestamp = current_time - philo->data->start_time;
		    printf("%lld %d died\n", death_timestamp, philo->id);
            exit(EXIT_FAILURE);
        }
        if (philo->data->max_meals > 0 && current_meal >= philo->data->max_meals)
            exit(EXIT_SUCCESS);
        usleep(1000);
    }
    return (NULL);
}

void    routine(t_philo *philo)
{
    if (philo->id % 2 == 0)
        ft_usleep(philo->data->time_to_eat / 2, philo->data);
    while(true)
    {
        // Picking fork
        sem_wait(philo->data->forks_sem);
        print_status(philo, PICKING_MSG);
        if (philo->data->num_philos == 1)
            ft_usleep(philo->data->time_to_die * 2, philo->data);
        sem_wait(philo->data->forks_sem);
        print_status(philo, PICKING_MSG);
        // Eating
        sem_wait(philo->data->meal_sem);
        philo->last_meal_time = get_time_in_ms();
        philo->meals_eaten++;
        sem_post(philo->data->meal_sem);
        print_status(philo, EATING_MSG);
        ft_usleep(philo->data->time_to_eat, philo->data);

        sem_post(philo->data->forks_sem);
        sem_post(philo->data->forks_sem);

        print_status(philo, SLEEPING_MSG);
        ft_usleep(philo->data->time_to_sleep, philo->data);
        thinking(philo);
    }

}

static void	thinking(t_philo *philo)
{
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	think_time;

	think_time = 0;
	time_to_eat = philo->data->time_to_eat;
	time_to_sleep = philo->data->time_to_sleep;
	print_status(philo, "is thinking");
	if (philo->data->num_philos % 2 == 0)
	{
		if (time_to_eat > time_to_sleep)
			think_time = time_to_eat - time_to_sleep;
	}
	else
		think_time = (time_to_eat * 2) - time_to_sleep;
	if (think_time > 5)
		think_time -= 5;
	else
		think_time = 0;
	if (think_time > 0)
	{
		if (think_time > philo->data->time_to_die / 2)
			think_time = philo->data->time_to_die / 2;
		ft_usleep(think_time, philo->data);
	}
}

void    philosopher(t_philo *philo)
{
    if (pthread_create(&philo->thread_id, NULL, &monitor, philo) != 0)
        exit(EXIT_FAILURE);
    pthread_detach(philo->thread_id);
    routine(philo);
    exit(EXIT_SUCCESS);
}
