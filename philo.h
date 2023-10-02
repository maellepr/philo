/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:24 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/02 16:57:34 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct	s_program
{
	int				nb_p;// max 200

	int				t_die;//temps qu'un philo meurt sil ne mange pas	min 60ms
	int				t_eat;//temps que prend un philo pour manger
	int				t_sleep;//temos que prend un philo pour dormir
	int				nb_eat;//nombre de fois un philo doit manger avant fin

	pthread_mutex_t	*lock_write;

	t_philo		**philos;//tableau avec tous les philo
	
}	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;

	int				spoon[2];
	pthread_mutex_t	*locks_spoon;

	t_program		*table;
}	t_philo;



/*------------------------- philo.c -------------------------*/
int			check_param(char **av);
int			check_nb_time(t_program *table);
void		print_struct(t_program *table);
t_philo		**init_philo(t_program *table);
t_program	*init_table(int ac, char **av);
void		philo(int ac, char **av);
int			main(int ac, char **av);

/*---------------------- philo_utils.c ----------------------*/
int			ft_atoi(const char *str);

/*---------------------- thread.c ----------------------*/
void		*routine(void *arg);
// int		create_a_thread(pthread_t thread, t_philo *philo);
// int		join_thread(pthread_t thread);
int			make_threads(t_program *table);

/*----------------------- free.c -----------------------*/
void		ft_free_all(t_program *table);

#endif
