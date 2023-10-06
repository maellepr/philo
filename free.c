/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:55:01 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/06 13:45:06 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_program *table)
{
	int	i;

	i = 0;
	while(i < table->nb_p)
	{
		free(table->philo[i]);
		i++;
	}
	free(table->philo);
	// free(table->lock_write);
	free(table->locks_spoon);
	free(table);
}

void	destroy_all_mutex(t_program *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->lock_write);
	pthread_mutex_destroy(&table->lock_flag);
	pthread_mutex_destroy(&table->lock_meal);
	pthread_mutex_destroy(&table->lock_nb_eat);
	while (i < table->nb_p)
	{
		pthread_mutex_destroy(&table->locks_spoon[i]);
		i++;
	}
}
