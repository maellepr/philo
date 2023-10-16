/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:53:26 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/16 18:05:58 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	child_process(t_program *table, int i)
{
	if (table)
		printf("hello from process n %d\n", i);
	if (i % 2 != 0)//philo impairs attendent
		duration(table, table->d_eat);
	while (1)
	{
		spoon_eat_routine(table, i);
		sleep_routine(table, i);
		think_routine(table, i);
	}
	free_all(table);
	exit(0);
	// return (0);
}

int	make_process(t_program *table)
{
	int	i;

	i = 0;
	printf("nb philo = %d\n", table->nb_p);
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
		i++;
	}
	return (0);
}
