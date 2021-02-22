/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:51:12 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/22 14:23:19 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define ER_ARGUMENT	-1
# define ER_MALLOC		-2
# define ER_FORK		-3

# define EAT			0
# define THINK			1
# define SLEEP			2
# define DIE			3

typedef struct		s_philo {
	int				num;
	int				state;
	int				limit;
	int				last_meal;
	pid_t			pid;
	struct s_data	*data;
	int				num_eat;
}					t_philo;

typedef struct		s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				start_time;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*helper;
	int				someone_dead;
}					t_data;

/*
**		main.c
*/
t_philo				*init_philos(t_data *data);
t_data				*init_data(char **argv);
int					check_args(int argc, char **argv);
int					create_process(t_philo *philo);
void				*check_eat_count(t_data *data);
/*
**		actions.c
*/
void				*actions(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
/*
**		wathcing.c
*/
void				*watching(t_philo *philo);
/*
**		utils.c
*/
int					ft_atoi(const char *nptr);
void				display(t_philo *philo, char *msg);
int					time_now();
int					error(int er_num);
int					min_lastmeal(t_data *data);
/*
**		clear.c
*/
void				clear(t_data *data);

#endif
