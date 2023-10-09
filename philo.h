/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:24 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/06 12:44:32 by mapoirie         ###   ########.fr       */
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

	long int		d_die;//duree qu'un philo meurt sil ne mange pas	min 60ms
	long int		d_eat;//duree que prend un philo pour manger
	long int		d_sleep;//duree que prend un philo pour dormir
	long int		nb_eat;//nombre de fois un philo doit manger avant fin

	long int		t_start;//temps ou le programme commence

	int				flag_stop;
	int				flag_eat;

	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_flag;
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	*locks_spoon;
	pthread_mutex_t	lock_nb_eat;

	// pthread_mutex_t lock_n_eat;


	t_philo			**philo;//tableau avec tous les philo
	
}	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;

	int				spoon[2];

//propre a chaque philo :

	long int		t_beg_meal;//temps debut de son dernier repas
	// long int		t_end_lastm;//temps fin de son dernier repas
	// long int		t_beg_meal;//temps debut de son dernier repas

	long int		nb_eat_each;



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

/*------------------------- thread.c ------------------------*/
int			time_die_reach(t_program *table);
int			check_conditions(t_program *table);
int			join_destroy_threads(t_program *table);
int			make_threads(t_program *table);

/*------------------------- routine.c ------------------------*/
int			spoon_eat_routine(void *info);
void		*routine(void *arg);

/*-------------------------- time.c --------------------------*/
long int	get_ms_time();
long int	time_since_beg(t_philo *philo);
int			check_flag(t_philo *philo);
int			duration(t_philo *philo, long int time, int x);
/*-------------------------- free.c --------------------------*/
void		free_all(t_program *table);
void		destroy_all_mutex(t_program *table);
#endif
