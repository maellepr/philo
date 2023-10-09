/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:24 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/09 18:00:02 by mapoirie         ###   ########.fr       */
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

typedef struct s_program
{
	int				nb_p;
	long int		d_die;
	long int		d_eat;
	long int		d_sleep;
	long int		nb_eat;
	long int		t_start;
	int				flag_stop;
	int				flag_eat;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_flag;
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	*locks_spoon;
	pthread_mutex_t	lock_nb_eat;
	t_philo			**philo;
}	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				spoon[2];
	long int		t_beg_meal;
	long int		nb_eat_each;
	t_program		*table;
}	t_philo;

/*------------------------- philo.c -------------------------*/
t_philo		**init_philo(t_program *table);
int			init_mutex(t_program *table);
int			init_nb_pre_atoi(t_program *table, int ac, char **av);
t_program	*init_table(int ac, char **av);
int			main(int ac, char **av);

/*---------------------- philo_utils.c ----------------------*/
int			ft_atoi(const char *str);
int			check_param(char **av);
void		assign_spoon(t_program *table, t_philo **philo, int i);

/*------------------------- thread.c ------------------------*/
int			each_eat_enought(t_program *table);
int			time_die_reach(t_program *table);
int			check_conditions(t_program *table);
int			join_destroy_threads(t_program *table);
int			make_threads(t_program *table);

/*------------------------- routine.c ------------------------*/
void		routine_alone(void *info);
int			sleep_routine(void *info);
int			think_routine(void *info);
void		*routine(void *arg);

/*------------------------- eat_routine.c ------------------------*/
int			take_fork_1(t_philo *philo);
int			take_fork_2(t_philo *philo);
int			is_eating(t_philo *philo);
int			spoon_eat_routine(void *info);

/*-------------------------- time.c --------------------------*/
long int	get_ms_time(void);
long int	time_since_beg(t_philo *philo);
int			check_flag(t_philo *philo);
int			duration(t_philo *philo, long int time, int x);

/*-------------------------- free.c --------------------------*/
void		free_all(t_program *table, int x);
void		destroy_all_mutex(t_program *table);
#endif
