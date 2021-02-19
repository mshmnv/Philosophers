/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/19 14:03:10 by lbagg            ###   ########.fr       */
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
		if (check_state(philo))
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

int		check_state(t_philo *philo)
{
	int	right_num;

	if (philo->left_fork->last_touch != philo->num &&
		philo->right_fork->last_touch != philo->num)
	{
		right_num = (philo->num - 1) % philo->data->num_philos;
		if (philo->num == 0)
			right_num = philo->data->num_philos - 1;
		if (philo->data->philos[(philo->num + 1) %
			philo->data->num_philos].state != EAT
			&& philo->data->philos[right_num].state != EAT)
			return (1);
	}
	return (0);
}
