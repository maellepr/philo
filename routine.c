/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:09:50 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/09 17:10:49 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_alone(void *info)
{
	t_philo	*philo;

	philo = info;
	pthread_mutex_lock(&philo->table->locks_spoon[philo->spoon[0]]);
	pthread_mutex_lock(&philo->table->lock_write);
	printf("%ld 1 has taken a fork\n", time_since_beg(philo));
	pthread_mutex_unlock(&philo->table->lock_write);
	pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
	usleep(philo->table->d_die * 1000);
	return ;
}

int	sleep_routine(void *info)
{
	t_philo	*philo;

	philo = info;
	if (check_flag(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->lock_write);
	if (check_flag(philo) != -1)
		printf("%ld %d is sleeping\n", time_since_beg(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->table->lock_write);
	if (duration(philo, philo->table->d_sleep, 1) == -1)
		return (-1);
	return (0);
}

int	think_routine(void *info)
{
	long int	time_to_think;
	t_philo		*philo;

	philo = info;
	if (check_flag(philo) == -1)
		return (-1);
	if (philo->table->nb_p % 2 == 0)
		time_to_think = philo->table->d_eat - philo->table->d_sleep;
	if (philo->table->nb_p % 2 != 0)
		time_to_think = philo->table->d_eat * 2 - philo->table->d_sleep;
	pthread_mutex_lock(&philo->table->lock_write);
	if (check_flag(philo) != -1)
		printf("%ld %d is thinking\n", time_since_beg(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->table->lock_write);
	if (duration(philo, time_to_think, 1) == -1)
		return (-1);
	return (0);
}

void	*routine(void *philo)
{
	if (((t_philo *)philo)->table->nb_p == 1)
		routine_alone(philo);
	else
	{	
		if (((t_philo *)philo)->id % 2 != 0)
		{
			if (duration(philo, ((t_philo *)philo)->table->d_eat, 1) == -1)
				return (NULL);
		}
		while (check_flag(philo) != -1)
		{
			if (spoon_eat_routine(philo) == -1)
				break ;
			if (sleep_routine(philo) == -1)
				break ;
			think_routine(philo);
		}
	}
	return (NULL);
}
