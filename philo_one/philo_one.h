/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:21:17 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/02 15:19:31 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define EAT		0
#define THINK	1
#define SLEEP	2
#define DIE		3
#define HUNGRY	4

typedef struct		s_philo {
	int				num;
	int				state;
	pthread_t		thread;
	int				limit;
	int				last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct		s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				not_dead;
	int				start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

/*
**		utils.c
*/

int	ft_atoi(const char *nptr);

/*
**		main.c
*/

void	init_philos(t_data *data);
t_data	*init_data(char **argv);
int		time_now();
void	clear(t_data *data);

/*
**		actions.c
*/

void	*actions(t_philo *philo);

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	die(t_philo *philo);

/*
**		display.c
*/
void	display(t_philo *philo, char *msg);

#endif