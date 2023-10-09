/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:11:50 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/09 17:59:50 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	each_eat_enought(t_program *table)
{
	int	i;

	i = 0;
	while (i < table->nb_p)
	{
		pthread_mutex_lock(&table->lock_nb_eat);
		if (table->philo[i]->nb_eat_each == table->nb_eat)
		{
			table->flag_eat += 1;
		}
		pthread_mutex_unlock(&table->lock_nb_eat);
		i++;
	}
	if (table->flag_eat == table->nb_p)
		return (-1);
	return (0);
}

int	time_die_reach(t_program *table)
{
	int	i;

	i = 0;
	while (i < table->nb_p)
	{
		pthread_mutex_lock(&table->lock_meal);
		if ((get_ms_time() - table->philo[i]->t_beg_meal) >= table->d_die)
		{
			pthread_mutex_lock(&table->lock_flag);
			table->flag_stop = -1;
			pthread_mutex_unlock(&table->lock_flag);
			pthread_mutex_lock(&table->lock_write);
			printf("%ld %d died\n", time_since_beg(table->philo[i]), i + 1);
			pthread_mutex_unlock(&table->lock_write);
			pthread_mutex_unlock(&table->lock_meal);
			return (-1);
		}
		pthread_mutex_unlock(&table->lock_meal);
		i++;
	}
	return (0);
}

int	check_conditions(t_program *table)
{
	if (table->nb_eat == 0)
		return (-1);
	if (table->d_die == 0)
		return (-1);
	while (1)
	{
		if (time_die_reach(table) == -1)
			return (-1);
		if (table->nb_eat > 0)
		{
			if (each_eat_enought(table) == -1)
				return (-1);
		}
		usleep(1000);
	}
	return (0);
}

int	join_destroy_threads(t_program *table)
{
	int	i;

	i = 0;
	while (i < table->nb_p)
	{
		if (pthread_join(table->philo[i]->thread, NULL) != 0)
			return (write(2, "Error while joining a thread\n", 29), -1);
		i++;
	}
	return (0);
}

int	make_threads(t_program *table)
{
	int	i;

	i = 0;
	while (i < table->nb_p)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, \
&routine, table->philo[i]) != 0)
			return (write(2, "Error while creating a thread\n", 30), -1);
		i++;
	}
	return (0);
}
