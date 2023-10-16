/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:54:26 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/16 17:56:26 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

// typedef struct s_philo	t_philo;

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
	sem_t			*sem_write;// init a 1 pour print 
	sem_t			*sem_meal;// init a 1
	sem_t			*sem_spoon;// init au nb de philo
	sem_t			*sem_nb_eat;// init a 1

	pid_t			*pid;
	// pthread_mutex_t	lock_write;
	// pthread_mutex_t	lock_flag;
	// pthread_mutex_t	lock_meal;
	// pthread_mutex_t	*locks_spoon;
	// pthread_mutex_t	lock_nb_eat;
	// t_philo			**philo;
}	t_program;

// typedef struct s_philo
// {
// 	// pthread_t		thread;
// 	// int				id;
// 	// int				spoon[2];
// 	// long int		t_beg_meal;
// 	// long int		nb_eat_each;
// 	t_program		*table;
// }	t_philo;

/*---------------------- philo_bonus.c ----------------------*/
int			main(int ac, char **av);
t_program	*init_table(int ac, char **av);
int			init_nb_pre_atoi(t_program *table, int ac, char **av);
int			init_sema(t_program *table);

/*------------------- philo_bonus_utils.c -------------------*/
int			ft_atoi(const char *str);
int			check_param(char **av);

/*---------------------- time.c ----------------------*/
long int	get_ms_time(void);
long int	time_since_beg(t_program *table);
void		duration(t_program *table, long int time);

/*---------------------- process.c ----------------------*/
int			make_process(t_program *table);
void		child_process(t_program *table, int i);

/*---------------------- routine.c ----------------------*/
void	eat_routine(t_program *table, int i);
void	sleep_routine(t_program *table, int i);
void	spoon_eat_routine(t_program *table, int i);

/*---------------------- free.c ----------------------*/
void		free_all(t_program *table);

#endif