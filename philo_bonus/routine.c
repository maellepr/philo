/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:47:17 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/16 18:02:32 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_routine(t_program *table, int i)
{
	
}

void	sleep_routine(t_program *table, int i)
{
	
}

void	spoon_eat_routine(t_program *table, int i)
{
	sem_wait(table->sem_spoon);//-1 a sem_spoon qui est init au nb de fork total (nb de philo)
	sem_wait(table->sem_write);//lock
	printf("%ld %d has taken a fork\n", time_since_beg(table), i);
	sem_post(table->sem_write);//unlock
	sem_wait(table->sem_spoon);//-1 a sem_spoon
	sem_wait(table->sem_write);
	printf("%ld %d has taken a second fork\n", time_since_beg(table), i);
	printf("%ld %d is eating\n", time_since_beg(table), i);
	sem_post(table->sem_write);
	duration(table, table->d_eat);//mange pendant duree du repas
	sem_post(table->sem_spoon);//+1 a sem_spoon, il repose une fork
	sem_post(table->sem_spoon);//+1 il repose deuxieme fork
	return ;
}