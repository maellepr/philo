/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:53:34 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/16 16:33:05 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sema(t_program *table)
{
	table->sem_write = sem_open("/lock_write", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_write == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	table->sem_meal = sem_open("/lock_meal", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_meal == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	table->sem_spoon = sem_open("/sem_spoon", O_CREAT, S_IRUSR | S_IWUSR, table->nb_p);
	if (table->sem_spoon == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	table->sem_nb_eat = sem_open("/sem_nb_eat", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_nb_eat == SEM_FAILED)
		return (write(2, "Error while opening semaphore\n", 30), -1);
	return (0);
}

int	init_nb_pre_atoi(t_program *table, int ac, char **av)
{
	table->nb_p = ft_atoi(av[1]);
	if (table->nb_p > 200)
		return (write(2, "Error, nb philo can't be more than 200\n", 39), -1);
	table->d_die = ft_atoi(av[2]);
	table->d_eat = ft_atoi(av[3]);
	table->d_sleep = ft_atoi(av[4]);
	if (ac == 5)
		table->nb_eat = -2;
	else if (ac == 6)
		table->nb_eat = ft_atoi(av[5]);
	if (table->nb_p == -1 || table->d_die == -1 || \
table->d_eat == -1 || table->d_sleep == -1 || table->nb_eat == -1)
		return (write(2, "Error, arguments has to be between 0 \
and int_max\n", 49), -1);
	return (0);
}

t_program	*init_table(int ac, char **av)
{
	t_program	*table;

	table = malloc(sizeof(t_program) * 1);
	if (!table)
		return (NULL);
	if (check_param(av) == -1)
		return (free(table), NULL);
	if (init_nb_pre_atoi(table, ac, av) == -1)
		return (free(table), NULL);
	table->t_start = get_ms_time();
	if (init_sema(table) == -1)
		return (free(table), NULL);
	table->pid = malloc(sizeof(pid_t) * table->nb_p);
	if (!table->pid)
		return (free(table), NULL);
	return (table);
}

int main(int ac, char **av)
{
	t_program	*table;

	table = NULL;
	if (ac == 5 || ac == 6)
	{
		table = init_table(ac, av);
		if (!table)
			return (1);
		if (table->nb_p == 0)
			return (0);
		if (make_process(table) == -1)
		{
			//quitter proprement
			free_all(table);
			return (1);
		}
		free_all(table);
	}
}