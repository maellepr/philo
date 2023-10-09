/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:00 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/09 17:13:49 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_ms_time(void)
{
	struct timeval	tv;
	long int		result;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}

long int	time_since_beg(t_philo *philo)
{
	long int		result;

	result = get_ms_time() - philo->table->t_start;
	return (result);
}

int	check_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock_flag);
	if (philo->table->flag_stop == -1)
	{
		pthread_mutex_unlock(&philo->table->lock_flag);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->lock_flag);
	return (0);
}

int	duration(t_philo *philo, long int time, int x)
{
	long int	time_end;

	time_end = get_ms_time() + time;
	while (get_ms_time() < time_end)
	{
		if (check_flag(philo) == -1 && x == 0)
		{
			pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[1]]);
			pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
			return (-1);
		}
		else if (check_flag(philo) == -1 && x == 1)
			return (-1);
		usleep(1000);
	}
	return (0);
}
