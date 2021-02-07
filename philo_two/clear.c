/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 20:08:20 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/07 18:16:39 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	clear(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->die_lock);
	sem_close(data->write_lock);
	sem_unlink("forks");
	sem_unlink("die");
	sem_unlink("write");
	free(data->philos);
	free(data);
}
