/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:09:17 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 13:34:13 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# define EXIT_SUCCESS		0
# define EXIT_FAILURE		1

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


int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
// void		ft_usleep(long time_in_ms, t_data *data);
long long	get_time_in_ms(void);

#endif
