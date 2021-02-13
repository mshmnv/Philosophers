/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:43:30 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/13 22:43:18 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	if (!(philos = (t_philo*)malloc(sizeof(t_philo) * data->num_philos)))
		return (NULL);
	while (i < data->num_philos)
	{
		philos[i].limit = 0;
		philos[i].state = THINK;
		philos[i].num = i;
		philos[i].data = data;
		i++;
	}
	return (philos);
}


t_data	*init_data(char **argv)
{
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	data->start_time = time_now();
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->forks_left = data->num_philos;
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->num_philos);
	sem_unlink("die");
	data->die_lock = sem_open("die", O_CREAT | O_EXCL, 0644, 1);
	sem_wait(data->die_lock);
	sem_unlink("write");
	data->write_lock = sem_open("write", O_CREAT | O_EXCL, 0644, 1);
	data->someone_dead = 0;
	return (data);
}

int		check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_atoi(argv[0]) < 2 || ft_atoi(argv[0]) > 200 || ft_atoi(argv[1]) < 60
		|| ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60)
		return (1);
	if (argc == 6)
		if (ft_atoi(argv[4]) < 0)
			return (1);
	return (0);
}

// void	check_loop(t_data *data)
// {
// 	int	i;
	
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->num_philos)
// 		{
// 			if (data->someone_dead)
// 				return ;
// 			if (data->philos[i].state != EAT && time_now() >= data->philos[i].limit)
// 			{
// 				data->philos[i].state = DIE;
// 				display(&data->philos[i], "died");
// 				data->someone_dead = 1;
// 				return ;
// 			}
// 			i++;
// 		}
// 		usleep(100);
// 	}
// }

int main(int argc, char **argv)
{
	int		i;
	t_data	*data;

	if (check_args(argc, argv + 1))
		return (error(ER_ARGUMENT));
	if (!(data = init_data(argv)))
		return (error(ER_MALLOC));
	if (!(data->philos = init_philos(data)))
		return (error(ER_MALLOC));
	data->num_to_eat = -1;
	if (argc == 6)
		data->num_to_eat = ft_atoi(argv[5]);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			(void*)&actions, &data->philos[i]);
		i++;
	}
	// check_loop(data);
	while (1)
	{
		i = 0;
		usleep(100);
		while (i < data->num_philos)
		{
			if (data->someone_dead)
				return (0);
			usleep(100);
			if (data->philos[i].state != EAT && time_now() > data->philos[i].limit)
			{
				data->philos[i].state = DIE;
				display(&data->philos[i], "died");
				data->someone_dead = 1;
				return (0);
			}
			i++;
		}
	}
	clear(data);
	return (0);
}