/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/06 20:19:52 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*watching(t_philo *philo)
{
	while (1)
	{
		if (philo->state != EAT && time_now() >= philo->limit)
		{
			philo->state = DIE;
			display(philo, "died");
			pthread_mutex_unlock(philo->data->die_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*actions(t_philo *philo)
{
	int			i;
	pthread_t	watch;

	i = 0;
	pthread_detach(philo->thread);
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	pthread_create(&watch, NULL, (void*)&watching, philo);
	pthread_detach(watch);
	while (philo->state != DIE && i != philo->data->num_to_eat)
	{
		if (check_state(philo))
			eating(philo);
		else
			continue;
		sleeping(philo);
		thinking(philo);
		i++;
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
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
