/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:54:26 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/18 16:54:38 by mapoirie         ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>

// typedef struct s_philo	t_philo;

typedef struct s_program
{
	int				nb_p;
	long int		d_die;
	long int		d_eat;
	long int		d_sleep;
	long int		nb_eat;

	long int		t_start;
	long int		t_beg_meal;

	int				flag_stop;
	// int				flag_eat;
	
	sem_t			*sem_write;
	sem_t			*sem_spoon;// init au nb de philo sert a bloquer nb de fork
	sem_t			*sem_nb_eat;// init a 0, sert a count nb de repas atteint par philo
	sem_t			*sem_dead;// sert a tuer tout le monde lorsqu un philo dead
	sem_t			*sem_flag;// sert a proteger variable flag_stop
	
	pid_t			*pid;

	pthread_t		thread_dead;
	pthread_t		thread_meal;
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
int			duration(long int time, t_program *table, int i);
int			check_conditions(t_program *table, int i);

/*---------------------- process.c ----------------------*/
int			open_sem(t_program *table);
void		child_process(t_program *table, int i);
int			make_process(t_program *table);


/*---------------------- routine.c ----------------------*/
int			think_routine(t_program *table, int i);
int			sleep_routine(t_program *table, int i);
int			spoon_eat_routine(t_program *table, int i, int count);

/*---------------------- thread.c ----------------------*/
int			check_flag_stop(t_program *philo);
void		*kill_process(void *info);
int			create_thread(t_program *table);

/*---------------------- free.c ----------------------*/
void		free_all(t_program *table);

#endif