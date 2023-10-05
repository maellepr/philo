/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:00 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/05 17:40:06 by mapoirie         ###   ########.fr       */
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

int	check_flag(t_philo *philo)
{
	if (philo->table->flag_stop == -1)
		return (-1);
	return (0);
}

int	duration(t_philo *philo, long int time)
{
	long int	time_end;

	time_end = get_ms_time() + time;
	while (get_ms_time() < time_end)
	{
		if (check_flag(philo) == -1)
			return (-1);
		usleep(1000);//1 milliseconde
	}
	return (0);
}
