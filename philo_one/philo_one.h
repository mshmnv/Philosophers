/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:21:17 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/30 19:35:32 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#include <unistd.h>

typedef struct		s_philo {
	int				num;
	pthread_t		thread;
	// int				left_fork;
	// int				right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct		s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				not_dead;
	pthread_mutex_t	*forks;
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

/*
**		actions.c
*/
void	*eating(t_philo *philo, t_data *data);
void	*sleeping(t_philo *philo, t_data *data);
void	*thinking(t_philo *philo);
void	*die(t_philo *philo, t_data *data);


#endif