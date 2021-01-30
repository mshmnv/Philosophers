/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/29 23:09:54 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);

	printf("%d is eating", philo->num);
	
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return NULL;
}

void	*sleep(t_philo *philo)
{
	printf("%d is sleeping", philo->num);
	return NULL;
}

void	*think(t_philo *philo)
{
	printf("%d is thinking", philo->num);
	return NULL;
}

void	*die(t_philo *philo)
{
	printf("%d died", philo->num);
	exit (0);
}