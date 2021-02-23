/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 20:08:20 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/23 12:58:24 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(data->forks[i].fork_mutex);
		free(data->forks[i].fork_mutex);
		pthread_mutex_destroy(data->philos[i].check);
		free(data->philos[i].check);
		i++;
	}
	pthread_mutex_destroy(data->write_lock);
	free(data->write_lock);
	pthread_mutex_destroy(data->die_lock);
	free(data->die_lock);
	free(data->forks);
	free(data->philos);
	free(data);
}
