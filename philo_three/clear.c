/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 20:08:20 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/22 14:15:45 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	clear(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("die");
	sem_unlink("write");
	sem_unlink("helper");
	free(data->philos);
	free(data);
}
