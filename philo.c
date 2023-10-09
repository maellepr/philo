/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:08 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/09 18:00:50 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philo(t_program *table)
{
	int		i;
	t_philo	**philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->nb_p);
	if (!philo)
		return (NULL);
	while (i < table->nb_p)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (!philo[i])
		{
			i = 0;
			while (philo[i])
				free(philo[i++]);
			return (free(philo), NULL);
		}
		philo[i]->id = i;
		philo[i]->table = table;
		assign_spoon(table, philo, i);
		philo[i]->t_beg_meal = get_ms_time();
		philo[i]->nb_eat_each = 0;
		i++;
	}
	return (philo);
}

int	init_mutex(t_program *table)
{
	int				i;
	pthread_mutex_t	*locks;

	i = 0;
	locks = malloc(sizeof(pthread_mutex_t) * table->nb_p);
	if (!locks)
		return (free(table), -1);
	while (i < table->nb_p)
	{
		pthread_mutex_init(&locks[i], NULL);
		i++;
	}
	table->locks_spoon = locks;
	pthread_mutex_init(&table->lock_write, NULL);
	pthread_mutex_init(&table->lock_flag, NULL);
	pthread_mutex_init(&table->lock_meal, NULL);
	pthread_mutex_init(&table->lock_nb_eat, NULL);
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
		return (NULL);
	if (init_nb_pre_atoi(table, ac, av) == -1)
		return (NULL);
	table->t_start = get_ms_time();
	table->flag_stop = 1;
	table->flag_eat = 0;
	if (init_mutex(table) == -1)
		return (NULL);
	table->philo = init_philo(table);
	if (!table->philo)
	{
		destroy_all_mutex(table);
		free_all(table, 0);
		return (NULL);
	}
	return (table);
}

int	main(int ac, char **av)
{
	t_program	*table;

	table = NULL;
	if (ac == 5 || ac == 6)
	{
		table = init_table(ac, av);
		if (!table)
			return (1);
		if (make_threads(table) == -1)
		{
			destroy_all_mutex(table);
			return (free_all(table, 1), 1);
		}
		if (check_conditions(table) == -1 || table->nb_p == 1)
			join_destroy_threads(table);
		destroy_all_mutex(table);
		free_all(table, 1);
	}
	else
		write(2, "Error, the program must take 4 or 5 arguments\n", 46);
	return (0);
}
