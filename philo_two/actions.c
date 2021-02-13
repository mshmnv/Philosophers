/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:49:54 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/13 21:11:03 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*actions(t_philo *philo)
{
	int			i;
	int flag = 0;
	i = 0;
	pthread_detach(philo->thread);
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	while (philo->state != DIE && i != philo->data->num_to_eat && !philo->data->someone_dead)
	{
		if (check_state(philo))
			eating(philo);
		else
		{	
			// if (philo->num == 3 && !flag)
			// {
			// flag = 1;
			// display(philo, "");
			// // 1
			// printf("%d{%d}\n",(philo->num + 1) % philo->data->num_philos,  (philo->data->philos[(philo->num + 1) % philo->data->num_philos].last_meal >= philo->last_meal));
			// // 3
			// printf("%d{%d}\n", (philo->num - 1) % philo->data->num_philos, (philo->data->philos[(philo->num - 1) % philo->data->num_philos].last_meal >= philo->last_meal));

			// }
			continue;
		}
		if (philo->state != DIE)
		// && !philo->data->someone_dead)
			sleeping(philo);
		if (philo->state != DIE)
		//  && !philo->data->someone_dead)
			thinking(philo);
		flag = 0;
			
		i++;
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	philo->last_meal = time_now();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	philo->state = EAT;
	philo->data->forks_left -= 2;
	sem_wait(philo->data->forks);
	display(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	display(philo, "has taken a fork");
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
