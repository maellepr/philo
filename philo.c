/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:08 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/02 17:36:40 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(char **av)
{
	int	i;
	int	j;

	i = 1;
	while(av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
			{
				write(2, "Error, arguments must be only digits\n", 37);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_nb_time(t_program *table)
{
	if (table->nb_p > 200)
		return(write(1, "Error, nb philo can't be more than 200\n", 39), -1);
	return(0);
}

void	print_struct(t_program *table)
{
	printf("nb_p = %d\n", table->nb_p);
	printf("t_die = %d\n", table->t_die);
	printf("t_eat = %d\n", table->t_eat);
	printf("t_sleep = %d\n", table->t_sleep);
	printf("nb_eat = %d\n", table->nb_eat);
}

void	assign_spoon(t_program *table, t_philo **philos, int i)
{
	if (i == 0)
	{
		philos[i]->spoon[0] = i;
		philos[i]->spoon[1] = table->nb_p - 1;
	}
	else
	{
		philos[i]->spoon[0] = i;
		philos[i]->spoon[1] = i - 1;
	}
	printf("philos->spoon[%d][0] = %d\n", i, philos[i]->spoon[0]);
	printf("philos->spoon[%d][1] = %d\n\n", i, philos[i]->spoon[1]);
}

t_philo	**init_philo(t_program *table)
{
	// philo->thread = calloc(philo->nb_p, sizeof(pthread_t));// a changer par ft_calloc
	// // philo->thread = malloc(sizeof(pthread_t) * (philo->nb_p));//p etre a remplir de null
	// if (!philo->thread)
	// 	return (-1);//erreur quitter programme
	// philo->i_thread = 0;
	int	i;

	t_philo	**philos;
	
	philos = malloc(sizeof(t_philo) * table->nb_p);
	if (!philos)
		return(NULL);
	i = 0;
	while(i < table->nb_p)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (NULL);
		philos[i]->id = i;
		philos[i]->table = table;
		philos[i]->locks_spoon = malloc(sizeof(pthread_mutex_t) * 1);// pas sur
		if (!philos[i]->locks_spoon)
			return(NULL);
		assign_spoon(table, philos, i);	
		i++;
	}
	return (philos);
}

t_program	*init_table(int ac, char **av)
{
	t_program	*table;

	table = malloc(sizeof(t_program) * 1);
	if (!table)
		return(NULL);
	if (check_param(av) == - 1)
		return (NULL);
	table->nb_p = ft_atoi(av[1]);
	table->t_die = ft_atoi(av[2]);
	table->t_eat = ft_atoi(av[3]);
	table->t_sleep = ft_atoi(av[4]);
	if (ac == 5)
		table->nb_eat = 1;//on choisi nous m comben de fois manger
	else if (ac == 6)
		table->nb_eat = ft_atoi(av[5]);	
	// print_struct(philo);
	table->lock_write = malloc(sizeof(pthread_mutex_t));
	table->philos = init_philo(table);
	if (check_nb_time(table) == - 1 || table->philos == NULL)
		return (NULL);
	return (table);
}
void	philo(int ac, char **av)
{
	t_program *table;

	table = NULL;
	table = init_table(ac, av);
	if (!table)
		return;
	// print_struct(table);
	make_threads(table);
	
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		philo(ac, av);
	else
		write(2, "Error, the program must take 4 or 5 arguments\n", 46);
}
