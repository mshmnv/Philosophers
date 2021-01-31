/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/31 18:29:00 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*actions(t_philo *philo)
{
	pthread_detach(philo->thread);
	while(philo->state != DIE)
	{
		
		if (philo->data->philos[(philo->num + 1) % 5].state != EAT && philo->data->philos[(philo->num - 1) % 5].state != EAT)
		{
			philo->limit = time_now() + philo->data->time_to_eat;
			eating(philo);
			usleep(200);
		}
		else
			continue;
		
		sleeping(philo);
		usleep(200);
		
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
	pthread_mutex_lock(philo->right_fork);

	printf("%d is eating\n", philo->num);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	philo->state = SLEEP;
	printf("%d is sleeping\n", philo->num);
}

void	thinking(t_philo *philo)
{
	philo->state = THINK;
	printf("%d is thinking\n", philo->num);
}

void	die(t_philo *philo)
{
	philo->state = DIE;
	printf("%d died\n", philo->num);
}

// void	*eating(t_philo *philo, t_data *data)
// {
// 	philo->state = EAT;
// 	pthread_detach(philo->thread);
// 	pthread_mutex_lock(philo->left_fork);
// 	pthread_mutex_lock(philo->right_fork);

// 	printf("%d is eating\n", philo->num);
// 	// usleep(data->time_to_eat);
	
// 	(void)data;
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// 	return NULL;
// }

// void	*sleeping(t_philo *philo, t_data *data)
// {
// 	philo->state = SLEEP;
// 	pthread_detach(philo->thread);
// 	printf("%d is sleeping\n", philo->num);
// 	// usleep(data->time_to_sleep);
// 	(void)data;
// 	return NULL;
// }

// void	*thinking(t_philo *philo)
// {
// 	philo->state = THINK;
// 	pthread_detach(philo->thread);
// 	printf("%d is thinking\n", philo->num);
// 	return NULL;
// }

// void	*die(t_philo *philo, t_data *data)
// {
// 	pthread_detach(philo->thread);
// 	data->not_dead = 0;
// 	printf("%d died\n", philo->num);
// 	return NULL;

// }