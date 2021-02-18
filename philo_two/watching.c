/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:34:16 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/18 13:55:17 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*watching(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (philo->num_eat == philo->data->num_to_eat)
			return (NULL);
		if (philo->state != EAT && time_now() > philo->limit)
		{
			philo->state = DIE;
			display(philo, "died");
			sem_post(philo->data->die_lock);
			return (NULL);
		}
	}
	return (NULL);
}
