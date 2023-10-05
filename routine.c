/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:09:50 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/05 17:53:13 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_routine(void *info)
{
	t_philo	*philo;

	philo = info;
	if (check_flag(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->lock_write);
	printf("%ld %d is sleeping\n", time_since_beg(philo), philo->id);
	pthread_mutex_unlock(&philo->table->lock_write);

	if (duration(philo, philo->table->d_sleep) == -1)
		return (-1);
	// usleep((((t_philo *)philo)->table->d_sleep) * 1000);
	return (0);
}

int	think_routine(void *info)
{
	t_philo	*philo;

	philo = info;
	if (check_flag(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->lock_write);
	printf("%ld %d is thinking\n", time_since_beg(philo), philo->id);
	pthread_mutex_unlock(&philo->table->lock_write);
	return (0);
}

int	spoon_eat_routine_even(void *info)
{
	t_philo	*philo;

	philo = info;
	if (check_flag(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->locks_spoon[philo->spoon[0]]);

	pthread_mutex_lock(&philo->table->lock_write);	
	printf("%ld %d has taken a fork\n", time_since_beg(philo), philo->id);
	pthread_mutex_unlock(&philo->table->lock_write);

	pthread_mutex_lock(&philo->table->locks_spoon[philo->spoon[1]]);

	pthread_mutex_lock(&philo->table->lock_write);
	printf("%ld %d has taken a fork\n", time_since_beg(philo), philo->id);
	pthread_mutex_unlock(&philo->table->lock_write);

	pthread_mutex_lock(&philo->table->lock_meal);
	philo->t_beg_meal = get_ms_time();
	pthread_mutex_unlock(&philo->table->lock_meal);
		
	pthread_mutex_lock(&philo->table->lock_write);
	printf("%ld %d is eating\n", time_since_beg(philo), philo->id);
	pthread_mutex_unlock(&philo->table->lock_write);

	if (duration(philo, philo->table->d_eat) == -1)//millisecondes
		return (-1);
	// usleep((((t_philo *)philo)->table->d_eat) * 1000);//peut-etre refaire un fonction plus precise pour faire wait

	//ajouter mutex peut-etre oui pour recuperer a l'exterieur le nb_eat
	philo->nb_eat_each += 1;
	//ajouter mutex
	
	pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[1]]);
	pthread_mutex_unlock(&philo->table->locks_spoon[philo->spoon[0]]);
	return (0);
}

void	*routine(void  *philo)
{
	// if (((t_philo *)philo)->table->nb_eat == 0)
	// 	return (NULL);
	// if (((t_philo *)philo)->table->d_die == 0)
	// 	return (NULL);

	while (check_flag(philo) != -1)
	{
		if (spoon_eat_routine_even(philo) == -1)//si nb de repas atteint
			break;
		if (sleep_routine(philo) == -1)
			break;
		think_routine(philo);
	}
	return (NULL);
}
