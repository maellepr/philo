/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:11:50 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/02 17:42:57 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spoon_eat_odd(void *philos)
{
	pthread_mutex_lock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[0]]);

	pthread_mutex_lock(((t_philo *)philos)->table->lock_write);
	printf("time Philosopher %d has taken a fork\n", ((t_philo *)philos)->id);
	pthread_mutex_unlock(((t_philo *)philos)->table->lock_write);
	
	pthread_mutex_lock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[1]]);

	pthread_mutex_lock(((t_philo *)philos)->table->lock_write);
	printf("time Philosopher %d has taken a fork\n", ((t_philo *)philos)->id);
	pthread_mutex_unlock(((t_philo *)philos)->table->lock_write);

	pthread_mutex_lock(((t_philo *)philos)->table->lock_write);
	printf("time Philosopher %d is eating\n", ((t_philo *)philos)->id);
	pthread_mutex_unlock(((t_philo *)philos)->table->lock_write);

	pthread_mutex_unlock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[1]]);
	pthread_mutex_unlock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[0]]);

}

void	spoon_eat_even(void *philos)
{
	pthread_mutex_lock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[1]]);

	pthread_mutex_lock(((t_philo *)philos)->table->lock_write);
	printf("time Philosopher %d has taken a fork\n", ((t_philo *)philos)->id);
	pthread_mutex_unlock(((t_philo *)philos)->table->lock_write);

	pthread_mutex_lock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[0]]);

	pthread_mutex_lock(((t_philo *)philos)->table->lock_write);
	printf("time Philosopher %d has taken a fork\n", ((t_philo *)philos)->id);
	pthread_mutex_unlock(((t_philo *)philos)->table->lock_write);

	pthread_mutex_lock(((t_philo *)philos)->table->lock_write);
	printf("time Philosopher %d is eating\n", ((t_philo *)philos)->id);
	pthread_mutex_unlock(((t_philo *)philos)->table->lock_write);

	pthread_mutex_unlock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[0]]);
	pthread_mutex_unlock(&((t_philo *)philos)->locks_spoon[((t_philo *)philos)->spoon[1]]);

}

void	*routine(void *philos)
{
	// if (philos)
	// write(1, "Hello from the thread num\n", 26);
	// pthread_mutex_lock(((t_philo *)philos)->table->lock_write);
	// printf("Hello from the thread num %d\n", ((t_philo *)philos)->id + 1);
	// pthread_mutex_unlock(((t_philo *)philos)->table->lock_write);
	if (((t_philo *)philos)->id % 2 == 0)
		spoon_eat_even(philos);
	else if (((t_philo *)philos)->id % 2 != 0)
		spoon_eat_odd(philos);
	// usleep(1000000);
	return (NULL);
}

int	make_threads(t_program *table)
{
	int i = 0;
	pthread_mutex_init(table->lock_write, NULL);

	while (i < table->nb_p)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &routine, table->philos[i]) != 0)
			perror("Erreur lors de la creation du thread");
		pthread_mutex_lock(table->lock_write);
		printf("Thread num %d cree\n", i + 1);
		pthread_mutex_unlock(table->lock_write);
		// create_a_thread(table->philos[i], philo);
		// pthread_mutex_lock(philo->write_lock);

		i++;
		// pthread_mutex_unlock(philo->write_lock);
	}
	i = 0;
	while (i < table->nb_p)
	{
		if (pthread_join(table->philos[i]->thread, NULL) != 0)
			perror("Erreur lors du join");
	
		i++;
		// pthread_mutex_unlock(philo->write_lock);

	}
	pthread_mutex_destroy(table->lock_write);
	ft_free_all(table);
	return (0);
}
