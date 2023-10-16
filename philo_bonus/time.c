/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:10:27 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/16 17:55:33 by mapoirie         ###   ########.fr       */
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

void	duration(t_program *table, long int time)
{
	long int	time_end;

	time_end = get_ms_time() + time;
	while (get_ms_time() < time_end)
		usleep(10000);//peut-etre a changer
	return ;
}