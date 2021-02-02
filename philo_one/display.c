/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:37:10 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/02 14:23:33 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	display(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%dms\t", (time_now() - philo->data->start_time));
	printf("%d ", philo->num + 1);
	printf("%s\n", msg);
	pthread_mutex_unlock(&philo->data->write_lock);

}