/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:20:48 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/29 23:13:06 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

#include "philo_one.h"

t_philo	**init_philos(int num_philo)
{
	int		i;
	t_philo	**philos;
	
	philos = (t_philo**)malloc(sizeof(t_philo*) * num_philo);
	i = 0;
	while (i < num_philo)
	{
		philos[i] = (t_philo*)malloc(sizeof(t_philo));
		philos[i]->num = i;
		pthread_mutex_init(philos[i]->left, NULL);
		pthread_mutex_init(philos[i]->right, NULL);
		i++;
	}
	return philos;	
}

int		main(int argc, char** argv)
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	
	if (argc != 5)
		return 0;
	num_philos = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);

	t_philo **philos = init_philos(num_philos);
	int i = 0;
	while (i < num_philos) {
		printf("%d\n", philos[i]->num);
		// pthread_create(philos[i]->thread, NULL, (void*)&eat, philos[i]);
		break;
		i++;
	}
	
	return 0;
}