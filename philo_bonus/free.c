/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:41:01 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/18 16:00:44 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_program *table)
{
	sem_close(table->sem_write);
	sem_close(table->sem_spoon);
	sem_close(table->sem_nb_eat);
	sem_close(table->sem_dead);
	sem_close(table->sem_flag);
	sem_unlink("/sem_write");
	sem_unlink("/sem_spoon");
	sem_unlink("/sem_nb_eat");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_flag");
	if (table->pid)
		free(table->pid);
	if (table)
		free(table);
}
