/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 00:59:50 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/06 00:59:50 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_atoi_number(const char *str, int sign);

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms, t_data *data)
{
	long long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_in_ms)
	{
		if (get_death_flag(data))
			break ;
		usleep(500);
	}
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		number;

	i = 0;
	sign = 0;
	number = 0;
	if (nptr == NULL)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (sign != 0)
			return (0);
		if (nptr[i++] == '-')
			sign = -1;
		else
			sign = 1;
	}
	if (sign == 0)
		sign = 1;
	number = ft_atoi_number(nptr + i, sign);
	return (number);
}

static int	ft_atoi_number(const char *str, int sign)
{
	int		i;
	int		number;
	long	tmp;

	i = 0;
	tmp = 0;
	number = 0;
	while (ft_isdigit(str[i]))
	{
		tmp = (tmp * 10) + str[i] - '0';
		i++;
	}
	if (tmp > INT_MAX && (tmp * sign != INT_MIN))
		number = 0;
	else if (tmp * sign == INT_MIN)
		return (INT_MIN);
	else if (tmp < INT_MIN)
		number = 0;
	else
		number = tmp;
	return (number * sign);
}
