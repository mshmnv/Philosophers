/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:21:17 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/23 12:53:16 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define ER_ARGUMENT	-1
# define ER_MALLOC		-2

# define EAT			0
# define THINK			1
# define SLEEP			2
# define DIE			3

typedef struct		s_forks
{
	pthread_mutex_t	*fork_mutex;
	int				last_touch;
}					t_forks;

typedef struct		s_philo {
	int				num;
	int				state;
	pthread_t		thread;
	int				limit;
	int				last_meal;
	t_forks			*left_fork;
	t_forks			*right_fork;
	struct s_data	*data;
	int				num_eat;
	pthread_mutex_t	*check;
}					t_philo;

typedef struct		s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				start_time;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*die_lock;
	t_philo			*philos;
	t_forks			*forks;
	int				someone_dead;
}					t_data;
/*
**		utils.c
*/
int					ft_atoi(const char *nptr);
void				display(t_philo *philo, char *msg);
int					time_now();
int					error(int er_num);
int					check_args(int argc, char **argv);
/*
**		watching.c
*/
void				*watching(t_philo *philo);
/*
**		main.c
*/
t_philo				*init_philos(t_data *data);
t_data				*init_data(char **argv);
int					init_mutexes(t_data *data);
void				check_eat_count(t_data *data);
/*
**		actions.c
*/
void				*actions(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
/*
**		clear.c
*/
void				clear(t_data *data);

#endif
