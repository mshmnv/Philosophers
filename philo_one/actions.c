/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/30 19:46:16 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*eating(t_philo *philo, t_data *data)
{
	// pthread_detach(philo->thread);
	// pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(philo->right_fork);

	// printf("%d is eating", philo->num);
	printf("is eating");

	(void)data;
	(void)philo;

	// usleep(data->time_to_eat);

	// pthread_mutex_unlock(philo->left_fork);
	// pthread_mutex_unlock(philo->right_fork);
	return NULL;
}

void	*sleeping(t_philo *philo, t_data *data)
{
	printf("%d is sleeping", philo->num);
	usleep(data->time_to_sleep);
	return NULL;
}

void	*thinking(t_philo *philo)
{
	printf("%d is thinking", philo->num);
	return NULL;
}

void	*die(t_philo *philo, t_data *data)
{
	data->not_dead = 0;
	printf("%d died", philo->num);
	return NULL;

}