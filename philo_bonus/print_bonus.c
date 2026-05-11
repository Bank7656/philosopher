#include "philosopher_bonus.h"

void	print_status(t_philo *philo, char *msg)
{
	long long	current_time;

	// if (get_death_flag(philo->data))
	// 	return ;
    sem_wait(philo->data->print_sem);
	current_time = get_time_in_ms() - philo->data->start_time;
	// if (!get_death_flag(philo->data))
	printf("%lld %d %s\n", current_time, philo->id, msg);
    sem_post(philo->data->print_sem);
}