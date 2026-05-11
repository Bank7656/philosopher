#include "philosopher_bonus.h"

void    *monitor(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    (void)philo;
    return (NULL);
}

void    routine(t_philo *philo)
{
    // Picking fork
    sem_wait(philo->data->forks_sem);
    print_status(philo, PICKING_MSG);
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
    

}

void    philosopher(t_philo *philo)
{
    if (pthread_create(&philo->thread_id, NULL, &monitor, philo) != 0)
        exit(EXIT_FAILURE);
    pthread_detach(philo->thread_id);
    routine(philo);
    exit(EXIT_SUCCESS);
}
