/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:07:33 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/22 14:23:32 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*watching(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (philo->num_eat == philo->data->num_to_eat)
			return (NULL);
		if (philo->data->someone_dead == 1)
			exit(0);
		if (philo->state != EAT && time_now() > philo->limit)
		{
			philo->state = DIE;
			philo->data->someone_dead = 1;
			display(philo, "died");
			exit(0);
		}
	}
}
