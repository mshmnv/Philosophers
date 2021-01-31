/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/31 19:43:45 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*actions(t_philo *philo)
{
	pthread_detach(philo->thread);
	philo->last_meal = time_now();
	while(philo->state != DIE)
	{
		
		if (philo->data->philos[(philo->num + 1) % 5].state != EAT && philo->data->philos[(philo->num - 1) % 5].state != EAT)
		{
			philo->limit = philo->last_meal + philo->data->time_to_die;
			eating(philo);
			usleep(philo->data->time_to_eat);
		}
		else
		{
			if (time_now() > philo->limit)
				die(philo);
			continue;
		}
		
		sleeping(philo);
		usleep(philo->data->time_to_sleep);
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
	printf("%d has taken a fork\n", philo->num + 1);
	pthread_mutex_lock(philo->right_fork);
	printf("%d has taken a fork\n", philo->num + 1);


	printf("%d is eating\n", philo->num + 1);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_meal = time_now();
}

void	sleeping(t_philo *philo)
{
	philo->state = SLEEP;
	printf("%d is sleeping\n", philo->num + 1);
}

void	thinking(t_philo *philo)
{
	philo->state = THINK;
	printf("%d is thinking\n", philo->num + 1);
}

void	die(t_philo *philo)
{
	philo->state = DIE;
	printf("%d died\n", philo->num + 1);
}
