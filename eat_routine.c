/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:28:38 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/09 18:28:35 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork_1(t_philo *philo)
{
	if (check_flag(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->locks_spoon[philo->spoon[0]]);
	pthread_mutex_lock(&philo->table->lock_write);
	if (check_flag(philo) != -1)
		printf("%ld %d has taken a fork\n", \
time_since_beg(philo), philo->id + 1);
	else if (check_flag(philo) == -1)
	{
		pthread_mutex_unlock(&philo->table->lock_write);
		pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->lock_write);
	return (0);
}

int	take_fork_2(t_philo *philo)
{
	if (check_flag(philo) == -1)
	{
		pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
		return (-1);
	}
	pthread_mutex_lock(&philo->table->locks_spoon[philo->spoon[1]]);
	pthread_mutex_lock(&philo->table->lock_write);
	if (check_flag(philo) != -1)
		printf("%ld %d has taken a fork\n", \
		time_since_beg(philo), philo->id + 1);
	else if (check_flag(philo) == -1)
	{	
		pthread_mutex_unlock(&philo->table->lock_write);
		pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
		pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[1]]);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->lock_write);
	return (0);
}

int	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock_write);
	if (check_flag(philo) != -1)
		printf("%ld %d is eating\n", time_since_beg(philo), philo->id + 1);
	else if (check_flag(philo) == -1)
	{
		pthread_mutex_unlock(&philo->table->lock_write);
		pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
		pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[1]]);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->lock_write);
	if (duration(philo, philo->table->d_eat, 0) == -1)
		return (-1);
	return (0);
}

int	spoon_eat_routine(void *info)
{
	t_philo	*philo;

	philo = info;
	if (take_fork_1(philo) == -1)
		return (-1);
	if (take_fork_2(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->lock_meal);
	philo->t_beg_meal = get_ms_time();
	pthread_mutex_unlock(&philo->table->lock_meal);
	if (is_eating(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->lock_nb_eat);
	philo->nb_eat_each += 1;
	pthread_mutex_unlock(&philo->table->lock_nb_eat);
	pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[1]]);
	pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
	if (philo->nb_eat_each == philo->table->nb_eat)
		return (-1);
	return (0);
}
