/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:09:50 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/04 17:34:23 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_routine(void *info)
{
	t_philo	*philo;

	philo = info;
	pthread_mutex_lock(philo->table->lock_write);
	printf("%ldms philosopher %d is sleeping\n", time_since_beg(philo), philo->id + 1);
	pthread_mutex_unlock(philo->table->lock_write);

	if (duration(philo, philo->table->d_sleep) == -1)
		return (-1);
	// usleep((((t_philo *)philo)->table->d_sleep) * 1000);
	return (0);
}

void	think_routine(void *info)
{
	t_philo	*philo;

	philo = info;
	pthread_mutex_lock(philo->table->lock_write);
	printf("%ldms philosopher %d is thinking\n", time_since_beg(philo), philo->id + 1);
	pthread_mutex_unlock(philo->table->lock_write);
}

int	spoon_eat_routine(void *info)
{
	t_philo	*philo;

	philo = info;
	pthread_mutex_lock(&philo->table->locks_spoon[philo->spoon[1]]);

	pthread_mutex_lock(philo->table->lock_write);	
	printf("%ldms philosopher %d has taken fork %d\n", time_since_beg(philo), philo->id + 1, philo->spoon[1]);
	pthread_mutex_unlock(philo->table->lock_write);

	pthread_mutex_lock(&philo->table->locks_spoon[philo->spoon[0]]);

	pthread_mutex_lock(philo->table->lock_write);
	printf("%ldms time philosopher %d has taken fork %d\n", time_since_beg(philo), philo->id + 1, philo->spoon[0]);
	pthread_mutex_unlock(((t_philo *)philo)->table->lock_write);
	
	//ajout mutex peut-etre
	// pthread_mutex_lock(((t_philo *)philo)->table->lock_write)
	philo->t_beg_lastm = time_since_beg(philo);
	//ajout mutex peut-etre
	// pthread_mutex_unlock(((t_philo *)philo)->table->lock_write);
	
	
	pthread_mutex_lock(philo->table->lock_write);
	printf("%ldms time philosopher %d is eating // num %ld\n", time_since_beg(philo), philo->id + 1, philo->nb_eat_each);
	pthread_mutex_unlock(philo->table->lock_write);

	pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
	pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[1]]);

	if (duration(philo, philo->table->d_eat) == -1)//millisecondes
		return (-1);
	// usleep((((t_philo *)philo)->table->d_eat) * 1000);//peut-etre refaire un fonction plus precise pour faire wait

	//ajouter mutex peut-etre
	philo->nb_eat_each += 1;
	//ajouter mutex peut-etre
	return (0);
}

void	*routine(void  *philo)
{
	if (((t_philo *)philo)->table->nb_eat == 0)
		return (NULL);
	if (((t_philo *)philo)->table->d_die == 0)
		return (NULL);

	while (1)
	{
		if (spoon_eat_routine(philo) == -1)//si nb de repas atteint
			break;
		if (sleep_routine(philo) == -1)
			break;
		think_routine(philo);
	}
	return (NULL);
}
