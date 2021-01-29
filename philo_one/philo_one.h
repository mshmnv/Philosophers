/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:21:17 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/29 16:06:07 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>

typedef struct		s_philo {
	int				num;
	pthread_t		*thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

}					t_philo;

/*
**		UTILS
*/

int	ft_atoi(const char *nptr);

/*
**		PHILOS
*/

t_philo	*init_philos(int num_philo);

#endif