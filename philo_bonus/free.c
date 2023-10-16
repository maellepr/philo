/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:41:01 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/16 16:40:35 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_program *table)
{
	sem_close(table->sem_write);
	sem_close(table->sem_meal);
	sem_close(table->sem_spoon);
	sem_close(table->sem_nb_eat);
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	sem_unlink("/sem_spoon");
	sem_unlink("/sem_nb_eat");
	if (table->pid)
		free(table->pid);
	if (table)
		free(table);
}
