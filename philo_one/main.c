/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:20:48 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/30 22:30:06 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// + check_input

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

// + вилка с большим номером + вилка с меньшим номером
// - вилка с меньшим номером - вилка с большим

#include "philo_one.h"

void	init_philos(t_data *data)
{
	int		i;
	
	i = 0;
	data->philos = (t_philo*)malloc(sizeof(t_philo) * data->num_philos);
	while (i < data->num_philos)
	{
		data->philos[i].num = i;
		// data->philos[i].right_fork = i;
		// data->philos[i].left_fork = (i + 1) % data->num_philos;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}

t_data	*init_data(char **argv)
{
	t_data	*data;
	int i;

	data = (t_data*)malloc(sizeof(t_data));
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->not_dead = 1;
	data->forks = (pthread_mutex_t	*)malloc(sizeof(pthread_mutex_t) * data->num_philos);
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return data;
}

int		main(int argc, char **argv)
{
	t_data	*data;
	int		i;
	
	if (argc != 5)
		return 0;
	data = init_data(argv);
	init_philos(data);
	i = 0;
	while (data->not_dead) {		
		i = 1;
		pthread_create(&data->philos[i].thread, NULL, (void*)&eating, &data->philos[i]);
		pthread_create(&data->philos[i].thread, NULL, (void*)&sleeping, &data->philos[i]);
		pthread_create(&data->philos[i].thread, NULL, (void*)&thinking, &data->philos[i]);

		i = 3;
		// pthread_create(&data->philos[i].thread, NULL, (void*)&eating, &data->philos[i]);

		break;
	}
	usleep(200);
	return 0;
}