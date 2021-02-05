/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:20:48 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/05 22:48:17 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// + num_to_eat

#include "philo_one.h"

t_philo		*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;
	
	i = 0;
	if (!(philos = (t_philo*)malloc(sizeof(t_philo) * data->num_philos)))
		return NULL;
	while (i < data->num_philos)
	{
		philos[i].limit = 0;
		philos[i].state = THINK;
		philos[i].num = i;
		philos[i].right_fork = &data->forks[i];
		philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		philos[i].data = data;
		i++;
	}
	return (philos);
}

t_data		*init_data(char **argv)
{
	t_data	*data;
	int i;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return NULL;
	data->start_time = time_now();
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);	
	data->time_to_sleep = ft_atoi(argv[4]);
	data->not_dead = 1;
	data->num_to_eat = 0;
	if (!(data->write_lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return NULL;
	pthread_mutex_init(data->write_lock, NULL);
	if (!(data->forks = (t_forks*)malloc(sizeof(t_forks) * data->num_philos)))
		return NULL;
	i = 0;
	while (i < data->num_philos)
	{
		if (!(data->forks[i].fork_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
			return NULL;
		pthread_mutex_init(data->forks[i].fork_mutex, NULL);
		data->forks[i].last_touch = -1;
		i++;
	}
	if (!(data->philos = init_philos(data)))
		return NULL;
	return data;
}

void	clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(data->forks[i].fork_mutex);
		i++;
	}
	free(data->write_lock);
	pthread_mutex_destroy(data->write_lock);
	free(data->forks);
	free(data->philos);
	free(data);
}

int		time_now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int		main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (argc != 5 && argc  != 6)
		return error(ER_ARGUMENT);
	if (!(data = init_data(argv)))
		return error(ER_MALLOC);
	if (argc == 6)
		data->num_to_eat = ft_atoi(argv[5]);
	if (data->num_philos < 2 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->num_to_eat < 0)
		return error(ER_ARGUMENT);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, (void*)&actions, &data->philos[i]);
		usleep(100);
		i++;
	}
	while (data->not_dead) {	
		NULL;
	}
	clear(data);
	return 0;
}