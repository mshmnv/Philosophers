/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/02 15:22:59 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*actions(t_philo *philo)
{
	pthread_detach(philo->thread);
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	while(philo->state != DIE)
	{
		if ((time_now() - philo->last_meal) < philo->data->time_to_eat)
			philo->state = HUNGRY;
		if (philo->state == HUNGRY && philo->data->philos[(philo->num + 1) % 5].state != EAT && philo->data->philos[(philo->num - 1) % 5].state != EAT)
		{
			eating(philo);
			philo->limit = philo->last_meal + philo->data->time_to_die;
		}
		else
		{
			if (time_now() > philo->limit)
				die(philo);
			continue;
		}
		sleeping(philo);
		thinking(philo);
		if (time_now() > philo->limit)
			die(philo);
	}
	philo->data->not_dead = 0;
	return NULL;
}


void	eating(t_philo *philo)
{
	philo->state = EAT;
	pthread_mutex_lock(philo->left_fork);
	display(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	display(philo, "has taken a fork");

	display(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_meal = time_now();
}

void	sleeping(t_philo *philo)
{
	philo->state = SLEEP;
	display(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	philo->state = THINK;
	display(philo, "is thinking");
}

void	die(t_philo *philo)
{
	usleep(1000);
	philo->state = DIE;
	display(philo, "died");
}
