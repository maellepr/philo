/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:00 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/04 17:35:26 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_ms_time()
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
	return(result);
}
int	duration(t_philo *philo, long int time)
{
	long int	time_end;

	time_end = get_ms_time() + time;
	while (get_ms_time() < time_end)
	{
		// faire une condition si philosophe meurt ou nb_eat atteint par tous
		if (philo->nb_eat_each == philo->table->nb_eat - 1)
			return (-1);
		// printf("actual time %ld - (t_beg_pr %ld + tbegin_lmeal %ld) = %ld > %ld\n", \
		// get_ms_time(), philo->table->t_start, philo->t_beg_lastm, (get_ms_time() - (philo->table->t_start + philo->t_beg_lastm)), philo->table->d_die);

		if ((get_ms_time() - (philo->table->t_start + philo->t_beg_lastm)) > philo->table->d_die)
		{
			pthread_mutex_lock(philo->table->lock_write);		
			printf("%ldms time philosopher %d died\n", time_since_beg(philo), philo->id + 1);			
			pthread_mutex_unlock(philo->table->lock_write);
			return (-1);
		}
		usleep(1000);//1 milliseconde
	}
	return (0);
}
