/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:35:24 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/18 18:03:36 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_flag_stop(t_program *table)
{
	while (1)
	{
		sem_wait(table->sem_flag);
		if (table->flag_stop == -1)
		{
			sem_post(table->sem_flag);	
			return (-1);
		}
		sem_post(table->sem_flag);
		usleep(1000);
	}
	return (0);
}

void	*kill_process(void *info)
{
	int			i;
	t_program	*table;

	i = 0;
	table = info;
	
	sem_wait(table->sem_dead);
	// if ( == -1)
	// 	return (NULL);
	while (i < table->nb_p)
	{
		kill(table->pid[i], SIGKILL);
		printf("process %d kill depuis kill_process\n", i);
		i++;
	}
	i = 0;
	while (i < table->nb_p)//permet de debloquer l'autre thread
	{
		sem_post(table->sem_nb_eat);
		i++;
	}
	sem_wait(table->sem_flag);
	table->flag_stop = -1;//le proteger avec sem
	sem_post(table->sem_flag);
	
	return (NULL);
}

void	*count_meal(void *info)
{
	int			i;
	t_program	*table;

	i = 0;
	table = info;
	while (i < table->nb_p)
	{
		sem_wait(table->sem_nb_eat);
		printf("sem nb_eat du philo %d debloque\n", i + 1);
		i++;
	}
	sem_wait(table->sem_flag);	
	if (table->flag_stop == -1)
	{
		sem_post(table->sem_flag);
		return (NULL);
	}
	sem_post(table->sem_flag);
	i = 0;
	while (i < table->nb_p)
	{
		kill(table->pid[i], SIGKILL);
		printf("process %d kill depuis count meal\n", i);
		i++;
	}
	sem_post(table->sem_dead);//debloque l'autre thread
	sem_wait(table->sem_flag);
	table->flag_stop = -1;//le proteger par un sem
	sem_post(table->sem_flag);		

	return (NULL);
}

int	create_thread(t_program *table)
{
	pthread_create(&table->thread_dead, NULL, &kill_process, table);
	if (table->nb_eat > 0)
		pthread_create(&table->thread_meal, NULL, &count_meal, table);
	if (check_flag_stop(table) == -1)
	{
		pthread_join(table->thread_dead, NULL);
		if (table->nb_eat > 0)
			pthread_join(table->thread_meal, NULL);
	}
	return (0);
}
