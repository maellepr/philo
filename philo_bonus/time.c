/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:10:27 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/18 10:53:46 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	get_ms_time(void)
{
	struct timeval	tv;
	long int		result;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}

long int	time_since_beg(t_program *table)
{
	long int		result;

	result = get_ms_time() - table->t_start;
	return (result);
}

int	duration(long int time, t_program *table, int i)
{
	long int	time_end;

	time_end = get_ms_time() + time;
	while (get_ms_time() < time_end)
	{
		if (check_conditions(table, i) == - 1)
			return (-1);
		usleep(1000);//peut-etre a changer
	}
	return (0);
}

int	check_conditions(t_program *table, int i)
{
		if ((get_ms_time() - table->t_beg_meal) >= table->d_die || table->d_die == 0)
		{
			printf("%ld %d died\n", time_since_beg(table), i + 1);
			sem_post(table->sem_dead);
			// printf("---->%d\n", sem_wait(table->sem_dead));
			usleep(1000);
			// sem_wait(table->sem_dead);
			return (-1);
		}
	return (0);
}
