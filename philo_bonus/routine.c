/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:47:17 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/18 17:55:48 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	think_routine(t_program *table, int i)
{
	long int	time_to_think;

	if (table->nb_p % 2 == 0)
		time_to_think = table->d_eat - table->d_sleep;		
	if (table->nb_p % 2 != 0)
		time_to_think = table->d_eat * 2 - table->d_sleep;
	if (check_conditions(table, i) == - 1)
		return (-1);
	printf("%ld %d is thinking\n", time_since_beg(table), i + 1);
	duration(time_to_think, table, i);
	return (0);
}

int	sleep_routine(t_program *table, int i)
{
	if (check_conditions(table, i) == - 1)
		return (-1);
	printf("%ld %d is sleeping\n", time_since_beg(table), i + 1);
	duration(table->d_sleep, table, i);
	return (0);
}

int	spoon_eat_routine(t_program *table, int i, int count)
{
	if (check_conditions(table, i) == - 1)
		return (-1);
	sem_wait(table->sem_spoon);//-1 a sem_spoon qui est init au nb de fork total (nb de philo)

	if (check_conditions(table, i) == - 1)
		return (-1);
	printf("%ld %d has taken a fork\n", time_since_beg(table), i + 1);

	sem_wait(table->sem_spoon);//-1 a sem_spoon

	if (check_conditions(table, i) == - 1)
		return (-1);
	printf("%ld %d has taken a fork\n", time_since_beg(table), i + 1);
	table->t_beg_meal = get_ms_time();
	if (check_conditions(table, i) == - 1)
		return (-1);
	if (count == table->nb_eat)
		sem_post(table->sem_nb_eat);
	printf("%ld %d is eating\n", time_since_beg(table), i + 1);
	if (check_conditions(table, i) == - 1)
		return (-1);
	duration(table->d_eat, table, i);//mange pendant duree du repas
	sem_post(table->sem_spoon);//+1 a sem_spoon, il repose une fork
	sem_post(table->sem_spoon);//+1 il repose deuxieme fork
	return (0);
}
