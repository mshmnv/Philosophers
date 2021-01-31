/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:20:48 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/31 18:27:13 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// + check_input

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

// начиная с 1го, потом со 2го и тд
// смотреть едят ли философы рядом

#include "philo_one.h"

void	init_philos(t_data *data)
{
	int		i;
	
	i = 0;
	data->philos = (t_philo*)malloc(sizeof(t_philo) * data->num_philos);
	while (i < data->num_philos)
	{
		data->philos[i].limit = 0;
		data->philos[i].state = THINK;
		data->philos[i].num = i;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
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
	data->num_to_eat = -1;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philos(data);
	return data;
}

void	clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}

int		time_now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_usec);
}

int		main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (argc != 5 && argc  != 6)
		return 0;
	data = init_data(argv);
	if (argc == 6)
		data->num_to_eat = ft_atoi(argv[5]);

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, (void*)&actions, &data->philos[i]);
		i++;
	}

	while (data->not_dead) {	
		i = 0;
		
		// break;
	}
	
	// clear(data);
	return 0;
}