/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:47:01 by thacharo          #+#    #+#             */
/*   Updated: 2026/02/20 23:51:12 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>
#include <unistd.h>

int		check_input(char **argv);
int		check_number(char *arg);
t_data	*data_init(int argc, char **argv);
void	clear_data(t_data *data);
void	*routine(void *arg);
t_philo	*philos_init(t_data *data, int n);
int		thread_init(t_data *data, t_philo *philos, int n);
void	print_status(t_philo *philo, char *msg);
void	run_monitor_loop(t_data *data);
void	ft_usleep(long time_in_ms, t_data *data);

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	(void)philos;
	if (argc < 5 || argc > 6)
		return (1);
	if (!check_input(argv + 1))
		return (1);
	data = data_init(argc, argv);
	data -> philos = philos_init(data, data -> num_philo);
	if (thread_init(data, data -> philos, data -> num_philo))
		return (1);
	run_monitor_loop(data);
	clear_data(data);
	return (0);
}

void	run_monitor_loop(t_data *data)
{
	int	i;
	int finishing_eating_count;
	int	current_meals;
	long long time_passed;

	while (1)
	{
		i = 0;
		finishing_eating_count = 0;

		while (i < data -> num_philo)
		{
			pthread_mutex_lock(&data -> philos[i].meal_mutex);
			time_passed = get_time_in_ms() - data -> philos[i].last_meal_time;
			current_meals = data -> philos[i].meals_eaten;
			pthread_mutex_unlock(&data -> philos[i].meal_mutex);
			if (time_passed > data -> time_to_die)
			{
				print_status(&data -> philos[i], DYING_MSG);
				pthread_mutex_lock(&data -> stop_mutex);
				data -> is_dining = 0;
				pthread_mutex_unlock(&data -> stop_mutex);
				return ;
			}
			if (data -> must_eat_count != 1 && current_meals >= data -> must_eat_count)
			{
				finishing_eating_count++;
			}
			i++;
		}
		if ((data -> must_eat_count != -1) && (finishing_eating_count == data -> num_philo))
		{
			pthread_mutex_lock(&data -> stop_mutex);
			data -> is_dining = 0;
			pthread_mutex_unlock(&data -> stop_mutex);
			return ;
		}
	}
	return ;
}	

int	thread_init(t_data *data, t_philo *philos, int n)
{
	int	i;
	pthread_t	thread_id;

	i = 0;
	data -> start_time = get_time_in_ms();
	while (i < n)
	{
		philos[i].last_meal_time = data -> start_time;
		thread_id = (&philos[i]) -> thread_id;
		if (pthread_create(&thread_id, NULL, &routine, &philos[i]) != 0)
		{
			return (1);
		}
		if (pthread_detach(thread_id) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}



t_philo	*philos_init(t_data *data, int n)
{
	int		i;
	int		left_fork_pos;
	int		right_fork_pos;
	t_philo *philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	while (i < n)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = 0;
		philos[i].data = data;
		left_fork_pos = i;
		right_fork_pos = (i + 1) % n;
		philos[i].left_fork = &data -> forks[left_fork_pos];
		philos[i].right_fork = &data -> forks[right_fork_pos];
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	return (philos);
}

int	is_simulation_active(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data -> stop_mutex);
	status = data -> is_dining;
	pthread_mutex_unlock(&data -> stop_mutex);
	return (status);
}

void	*routine(void *arg)
{
	t_philo *philos;
	(void)arg;
	philos = (t_philo *)arg;
	while (is_simulation_active(philos -> data))
	{
		if (philos -> id % 2 != 0)
		{
			pthread_mutex_lock(philos -> left_fork);
			print_status(philos, PICKING_MSG);
			pthread_mutex_lock(philos -> right_fork);
			print_status(philos, PICKING_MSG);
		}
		else
		{
			pthread_mutex_lock(philos -> right_fork);
			print_status(philos, PICKING_MSG);	
			pthread_mutex_lock(philos -> left_fork);
			print_status(philos, PICKING_MSG);
		}

		pthread_mutex_lock(&philos -> meal_mutex);
		philos -> last_meal_time = get_time_in_ms();
		print_status(philos, EATING_MSG);
		philos -> meals_eaten++;
		pthread_mutex_unlock(&philos -> meal_mutex);
		ft_usleep(philos -> data -> time_to_eat, philos -> data);

		if (philos -> id % 2 != 0)
		{
			pthread_mutex_unlock(philos -> right_fork);
			pthread_mutex_unlock(philos -> left_fork);
		}
		else
		{
			pthread_mutex_unlock(philos -> left_fork);
			pthread_mutex_unlock(philos -> right_fork);
		}
		print_status(philos, SLEEPING_MSG);
		ft_usleep(philos -> data -> time_to_sleep, philos -> data);
		print_status(philos, THINKING_MSG);
		long think_time = 0;

		// If eating takes longer than sleeping, they MUST wait the difference 
		// plus a tiny buffer (like 5ms) to ensure the starving neighbor gets the forks first.
		if (philos->data->time_to_eat >= philos->data->time_to_sleep)
		{
			think_time = philos->data->time_to_eat - philos->data->time_to_sleep + 5;
		}
		else
		{
			// If sleeping is longer, they are naturally polite, but we still force 
			// a tiny 1ms yield to prevent CPU traffic jams in the 200-philo tests.
			think_time = 1;
		}

		// Use your precision sleep function to execute the thinking time
		ft_usleep(think_time, philos->data);
	}

	return (NULL);
}

void	ft_usleep(long time_in_ms, t_data *data)
{
	long	start_time;

	start_time = get_time_in_ms();
	while((get_time_in_ms() - start_time) < time_in_ms)
	{
		if (is_simulation_active(data) == 0)
			break;
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *msg)
{
	long long current_time;
	long long elasped_time;

	pthread_mutex_lock(&philo -> data -> write_mutex);
	if (is_simulation_active(philo -> data))
	{
		current_time = get_time_in_ms();
		elasped_time = current_time - philo -> data -> start_time;
		printf("%lld %i %s\n", elasped_time, philo -> id, msg);
	}
	pthread_mutex_unlock(&philo -> data -> write_mutex);
	return ;
}

void	clear_data(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data -> write_mutex);
	pthread_mutex_destroy(&data -> stop_mutex);
	i = 0;
	while (i < data -> num_philo)
	{
		pthread_mutex_destroy(&(data -> forks[i]));
		pthread_mutex_destroy(&data -> philos[i].meal_mutex);
		i++;
	}
	free(data -> philos);
	free(data -> forks);
	free(data);
}


