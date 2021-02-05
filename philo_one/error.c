/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:49:49 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/05 21:52:09 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	error(int er_num)
{
	if (er_num == ER_ARGUMENT)
		printf("Argument error");
	if (er_num == ER_MALLOC)
		printf("Malloc error");
	return 1;
}