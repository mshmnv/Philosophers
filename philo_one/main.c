/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:20:48 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/29 16:07:46 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

#include "philo_one.h"

void	*eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);

	printf("Philosopher %d is eating", philo->num);
	
	pthread_mutex_unlocklock(philo->left);
	pthread_mutex_unlocklock(philo->right);
}

void	*sleep(t_philo *philo)
{
	printf("Philosopher %d is sleeping", philo->num);
}

void	*think(t_philo *philo)
{
	printf("Philosopher %d is thinking", philo->num);
}

t_philo	*init_philos(int num_philo)
{
	int		i;
	t_philo	*philos;
	
	philos = (t_philo*)malloc(sizeof(t_philo) * num_philo);
	i = 0;
	while (i < num_philo)
	{
		philos[i].num = i;
		pthread_mutex_init(philos[i].left, NULL);
		pthread_mutex_init(philos[i].right, NULL);
		i++;
	}
	return philos;	
}

int		main(int argc, char** argv)
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	
	if (argc != 5)
		return 0;
	num_philo = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);

	t_philo *philos = init_philos(num_philo);
	
	return 0;
}