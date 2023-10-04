/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:08 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/04 15:04:56 by mapoirie         ###   ########.fr       */
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
	printf("t_die = %ld\n", table->d_die);
	printf("t_eat = %ld\n", table->d_eat);
	printf("t_sleep = %ld\n", table->d_sleep);
	printf("nb_eat = %ld\n", table->nb_eat);
}

void	assign_spoon(t_program *table, t_philo **philo, int i)
{
	if (philo[i]->id % 2 == 0)
	{
		philo[i]->spoon[0] = i;
		if (i == 0)
			philo[i]->spoon[1] = table->nb_p - 1;
		else
			philo[i]->spoon[1] = i - 1;
	}
	else if (philo[i]->id % 2 != 0)
	{
		if (i == 0)
			philo[i]->spoon[0] = table->nb_p - 1;
		else
			philo[i]->spoon[0] = i - 1;
		philo[i]->spoon[1] = i;		
	}
	// printf("philo->spoon[%d][0] = %d\n", i, philo[i]->spoon[0]);
	// printf("philo->spoon[%d][1] = %d\n\n", i, philo[i]->spoon[1]);
	return ;
}


t_philo	**init_philo(t_program *table)
{
	// philo->thread = calloc(philo->nb_p, sizeof(pthread_t));// a changer par ft_calloc
	// // philo->thread = malloc(sizeof(pthread_t) * (philo->nb_p));//p etre a remplir de null
	// if (!philo->thread)
	// 	return (-1);//erreur quitter programme
	// philo->i_thread = 0;
	int	i;

	t_philo	**philo;
	
	philo = malloc(sizeof(t_philo) * table->nb_p);
	if (!philo)
		return(NULL);
	i = 0;
	while(i < table->nb_p)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (NULL);
		philo[i]->id = i;

		// philo[i]->locks_spoon = malloc(sizeof(pthread_mutex_t));// pas sur
		// if (!philo[i]->locks_spoon)
		// 	return(NULL);
		philo[i]->table = table;		
		assign_spoon(table, philo, i);

		philo[i]->t_beg_lastm = 0;
		philo[i]->nb_eat_each = 0;
		i++;
	}
	return (philo);
}

pthread_mutex_t	*init_spoon_locks(t_program *table)
{
	int				i;
	pthread_mutex_t	*locks_spoon;

	i = 0;
	locks_spoon = malloc(sizeof(pthread_mutex_t) * table->nb_p);//ajouter protec
	while (i < table->nb_p)
	{
		pthread_mutex_init(&locks_spoon[i], NULL);
		i++;
	}
	return(locks_spoon);
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
	table->d_die = ft_atoi(av[2]);
	table->d_eat = ft_atoi(av[3]);
	table->d_sleep = ft_atoi(av[4]);
	if (ac == 5)
		table->nb_eat = -1;//faire a l'infini
	else if (ac == 6)
		table->nb_eat = ft_atoi(av[5]);
	table->t_start = get_ms_time();
	// print_struct(philo);
	table->lock_write = malloc(sizeof(pthread_mutex_t));// ajouter protec
	pthread_mutex_init(table->lock_write, NULL);
	table->locks_spoon = init_spoon_locks(table); 
	table->philo = init_philo(table);
	if (check_nb_time(table) == - 1 || table->philo == NULL)
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
	make_threads(table);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		philo(ac, av);
	else
		write(2, "Error, the program must take 4 or 5 arguments\n", 46);
}
