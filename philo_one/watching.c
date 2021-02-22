/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:54:04 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/22 10:55:16 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*watching(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (philo->num_eat == philo->data->num_to_eat
			|| philo->data->someone_dead)
			return (NULL);
		pthread_mutex_lock(philo->check);
		if (philo->state != EAT && time_now() > philo->limit)
		{
			philo->state = DIE;
			philo->data->someone_dead = 1;
			display(philo, "died");
			pthread_mutex_unlock(philo->data->die_lock);
			pthread_mutex_unlock(philo->check);
			return (NULL);
		}
		pthread_mutex_unlock(philo->check);
	}
	return (NULL);
}
