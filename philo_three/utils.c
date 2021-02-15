/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:45:43 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/15 14:58:51 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_atoi(const char *nptr)
{
	int				i;
	int				minus;
	long long int	res;
	long long int	check;

	i = 0;
	res = 0;
	minus = 1;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
			|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
		minus = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		check = res;
		res = res * 10 + nptr[i] - 48;
		if (check > res)
			return ((minus < 0) ? 0 : -1);
		i++;
	}
	return (res * minus);
}

int		time_now(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	display(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->data->write_lock);
	printf("%dms\t", (time_now() - philo->data->start_time));
	printf("%d ", philo->num + 1);
	printf("%s\n", msg);
	pthread_mutex_unlock(philo->data->write_lock);
}

// int		check_state(t_philo *philo)
// {
// 	int	right_num;

// 	if (philo->left_fork->last_touch != philo->num &&
// 		philo->right_fork->last_touch != philo->num)
// 	{
// 		right_num = (philo->num - 1) % philo->data->num_philos;
// 		if (philo->num == 0)
// 			right_num = philo->data->num_philos - 1;
// 		if (philo->data->philos[(philo->num + 1) %
// 			philo->data->num_philos].state != EAT
// 			&& philo->data->philos[right_num].state != EAT)
// 			return (1);
// 	}
// 	return (0);
// }

int		error(int er_num)
{
	if (er_num == ER_ARGUMENT)
		printf("Argument error");
	if (er_num == ER_MALLOC)
		printf("Malloc error");
	return (1);
}
