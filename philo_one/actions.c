/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/05 23:21:53 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*actions(t_philo *philo)
{
	pthread_detach(philo->thread);
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	while (philo->state != DIE)
	{
		if (philo->data->philos[(philo->num + 1) % philo->data->num_philos].state != EAT
			&& philo->data->philos[(philo->num - 1) % philo->data->num_philos].state != EAT
			&& philo->left_fork->last_touch != philo->num && philo->right_fork->last_touch != philo->num)
			eating(philo);
		else
		{
			if (time_now() >= philo->limit)
				die(philo);
			continue;
		}
		sleeping(philo);
		thinking(philo);
		if (time_now() >= philo->limit)
			die(philo);
	}
	return NULL;
}


void	eating(t_philo *philo)
{
	philo->state = EAT;
	pthread_mutex_lock(philo->left_fork->fork_mutex);
	philo->left_fork->last_touch = philo->num;
	display(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork->fork_mutex);
	philo->right_fork->last_touch = philo->num;
	display(philo, "has taken a fork");
	display(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork->fork_mutex);
	pthread_mutex_unlock(philo->right_fork->fork_mutex);
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
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
	// usleep(1000);
	philo->state = DIE;
	philo->data->not_dead = 0;
	display(philo, "died");
}
