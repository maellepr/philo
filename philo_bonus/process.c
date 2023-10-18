/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:53:26 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/18 16:55:23 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	open_sem(t_program *table)
{
	table->sem_write = sem_open("/lock_write", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_write == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	table->sem_spoon = sem_open("/sem_spoon", O_CREAT, S_IRUSR | S_IWUSR, table->nb_p);
	if (table->sem_spoon == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	table->sem_nb_eat = sem_open("/sem_nb_eat", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_nb_eat == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	table->sem_dead = sem_open("/sem_dead", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (table->sem_dead == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	table->sem_flag = sem_open("/sem_flag", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (table->sem_flag == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	return (0);
}

void	child_process(t_program *table, int i)
{
	int	count;

	count = 1;	
	if (open_sem(table) == -1)
		return ;
	if (i % 2 != 0)//philo impairs attendent
		duration(table->d_eat, table, i);
	while (1)
	{
		if (spoon_eat_routine(table, i, count) == -1)
			break;
		if (sleep_routine(table, i) == -1)
			break;
		if (think_routine(table, i) == -1)
			break;
		count++;
	}
	usleep(1000);
	// free_all(table);
	// exit(0);
	// return (0);
}

int	make_process(t_program *table)
{
	int	i;

	i = 0;
	// printf("nb philo = %d\n", table->nb_p);
	if (table->nb_eat == 0)
		return (-1);
	//ajouter cas quand philo alone
	while (i < table->nb_p)
	{
		table->pid[i] = fork();
		if (table->pid[i] == -1)
			return (-1);
		else if (table->pid[i] == 0)//on entre dans un child process
		{	
			child_process(table, i);
			// if (child_process(table, i) == -1)
			// 	return (-1);
		}
		// else if (table->pid[i] > 0)
		// {
		// 	//parent process
		// }
		usleep(1000);
		i++;
	}
	create_thread(table);
	waitpid(-1, NULL, 0);
	return (0);
}
