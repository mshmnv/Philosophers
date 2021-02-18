/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:53:43 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/17 09:45:11 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*watching(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (philo->state != EAT && time_now() > philo->limit)
		{
			philo->state = DIE;
			display(philo, "died");
			sem_post(philo->data->die_lock);
			return (NULL);
		}
	}
	return (NULL);
}

void	*actions(t_philo *philo)
{
	int			i;
	pthread_t	watch;
	
	i = 0;
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	pthread_create(&watch, NULL, (void*)&watching, philo);
	pthread_detach(watch);
	while (philo->state != DIE && i != philo->data->num_to_eat
		&& !philo->data->someone_dead)
	{
		if (check_state(philo))
			eating(philo);
		else
			continue;
		if (philo->state != DIE && !philo->data->someone_dead)
			sleeping(philo);
		if (philo->state != DIE && !philo->data->someone_dead)
			thinking(philo);
		i++;
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	philo->data->forks_left -= 2;
	sem_wait(philo->data->forks);
	display(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	display(philo, "has taken a fork");
	philo->state = EAT;
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	display(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->data->forks_left += 2;
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

	usleep(100);
	right_num = (philo->num - 1) % philo->data->num_philos;
	if (philo->num == 0)
		right_num = philo->data->num_philos - 1;
	if (philo->last_meal <= min_lastmeal(philo->data)
		&& philo->data->forks_left > 1)
		return (1);
	return (0);
}
