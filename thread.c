/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:11:50 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/04 15:05:55 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_threads(t_program *table)
{
	int i = 0;
	while (i < table->nb_p)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, &routine, table->philo[i]) != 0)
			perror("Erreur lors de la creation du thread");//a changer car perror non autorise
		// pthread_mutex_lock(table->lock_write);
		// printf("Thread num %d cree\n", i + 1);
		// pthread_mutex_unlock(table->lock_write);
		i++;
	}
	i = 0;
	while (i < table->nb_p)
	{
		if (pthread_join(table->philo[i]->thread, NULL) != 0)
			perror("Erreur lors du join");//a changer car perror non autorise
		i++;
	}
	destroy_all_mutex(table);
	free_all(table);
	return (0);
}
