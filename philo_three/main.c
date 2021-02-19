/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:50:55 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/19 15:04:53 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		philos[i].num_eat = 0;
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

int		create_process(t_philo *philo)
{
	philo->pid = fork();
	if (philo->pid < 0)
		return (1);
	else if (philo->pid == 0)
	{
		actions(philo);
		exit(0);
	}
	return (0);
}

// void	check_eat_count(t_data *data)
// {
// 	int	i;

// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->num_philos)
// 		{
// 			if (data->philos[i].num_eat != data->num_to_eat)
// 				i = data->num_philos;
// 			i++;
// 		}
// 		if (i == data->num_philos)
// 		{
// 			sem_post(data->die_lock);
// 			return ;
// 		}
// 	}
// }

int		main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (check_args(argc, argv + 1))
		return (error(ER_ARGUMENT));
	if (!(data = init_data(argv)))
		return (error(ER_MALLOC));
	if (!(data->philos = init_philos(data)))
		return (error(ER_MALLOC));
	data->num_to_eat = -1;
	if (argc == 6)
		data->num_to_eat = ft_atoi(argv[5]);
	i = -1;
	while (++i < data->num_philos)
		if (create_process(&data->philos[i]))
			return (error(ER_FORK));
	// if (data->num_to_eat != -1)
	// 	check_eat_count(data);
	sem_wait(data->die_lock);
	i = -1;
	while (++i < data->num_philos)
		kill(data->philos[i].pid, SIGKILL);
	clear(data);
	return (0);
}
