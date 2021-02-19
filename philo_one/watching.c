/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:54:04 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/19 14:53:26 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*watching(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (philo->state != EAT && time_now() >= philo->limit)
		{
			philo->state = DIE;
			display(philo, "died");
			pthread_mutex_unlock(philo->data->die_lock);
			return (NULL);
		}
	}
	return (NULL);
}
