/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/22 10:56:40 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*actions(t_philo *philo)
{
	pthread_t	watch;

	pthread_detach(philo->thread);
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	pthread_create(&watch, NULL, (void*)&watching, philo);
	pthread_detach(watch);
	while (philo->state != DIE && !philo->data->someone_dead
			&& philo->num_eat != philo->data->num_to_eat)
	{
		if (philo->left_fork->last_touch != philo->num &&
		philo->right_fork->last_touch != philo->num)
			eating(philo);
		else
			continue;
		philo->num_eat++;
		if (philo->state != DIE && !philo->data->someone_dead)
			sleeping(philo);
		if (philo->state != DIE && !philo->data->someone_dead)
			thinking(philo);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->left_fork->fork_mutex);
		philo->left_fork->last_touch = philo->num;
		display(philo, "has taken a fork");
	}
	pthread_mutex_lock(philo->right_fork->fork_mutex);
	philo->right_fork->last_touch = philo->num;
	display(philo, "has taken a fork");
	if (!(philo->num % 2))
	{
		pthread_mutex_lock(philo->left_fork->fork_mutex);
		philo->left_fork->last_touch = philo->num;
		display(philo, "has taken a fork");
	}
	pthread_mutex_lock(philo->check);
	philo->state = EAT;
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	pthread_mutex_unlock(philo->check);
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
