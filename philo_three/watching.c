/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:07:33 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/21 18:38:24 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*watching(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (philo->num_eat == philo->data->num_to_eat
			|| philo->data->someone_dead == 1)
			exit(0);
		if (philo->state != EAT && time_now() > philo->limit)
		{
			philo->state = DIE;
			philo->data->someone_dead = 1;
			display(philo, "died");
			sem_post(philo->data->die_lock);
			exit(0);
		}
	}
}
