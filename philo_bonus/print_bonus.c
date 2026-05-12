#include "philosopher_bonus.h"

void	print_status(t_philo *philo, char *msg)
{
	long long	current_time;

    sem_wait(philo->data->print_sem);
	current_time = get_time_in_ms() - philo->data->start_time;
	printf("%lld %d %s\n", current_time, philo->id, msg);
    sem_post(philo->data->print_sem);
}