/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:21:17 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/29 23:01:29 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct		s_philo {
	int				num;
	pthread_t		*thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

}					t_philo;

/*
**		utils.c
*/

int	ft_atoi(const char *nptr);

/*
**		main.c
*/

t_philo	**init_philos(int num_philo);
/*
**		actions.c
*/
void	*eat(t_philo *philo);
void	*sleep(t_philo *philo);
void	*think(t_philo *philo);
void	*die(t_philo *philo);


#endif