/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/30 22:49:36 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*actions(t_philo *philo, t_data *data)
{

	return NULL;
}

void	*eating(t_philo *philo, t_data *data)
{
	pthread_detach(philo->thread);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);

	printf("%d is eating\n", philo->num);
	// usleep(data->time_to_eat);
	
	(void)data;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return NULL;
}

void	*sleeping(t_philo *philo, t_data *data)
{
	pthread_detach(philo->thread);
	printf("%d is sleeping\n", philo->num);
	// usleep(data->time_to_sleep);
	(void)data;
	return NULL;
}

void	*thinking(t_philo *philo)
{
	pthread_detach(philo->thread);
	printf("%d is thinking\n", philo->num);
	return NULL;
}

void	*die(t_philo *philo, t_data *data)
{
	pthread_detach(philo->thread);
	data->not_dead = 0;
	printf("%d died\n", philo->num);
	return NULL;

}