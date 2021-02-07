/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:42:44 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/07 12:14:29 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

# define ER_ARGUMENT	-1
# define ER_MALLOC		-2

# define EAT			0
# define THINK			1
# define SLEEP			2
# define DIE			3

typedef struct		s_philo {
	int				num;
	int				num_to_eat;
	int				state;
	pthread_t		thread;
	int				limit;
	int				last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct		s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				start_time;
	t_philo			*philos;
	sem_t			*forks_sem;
	sem_t			*dead_sem;
	sem_t			*write_sem;

}					t_data;

/*
**		utils.c
*/
int					ft_atoi(const char *nptr);
void				display(t_philo *philo, char *msg);
int					check_args(int argc, char **argv);
int					time_now();
int					error(int er_num);
/*
**		clear.c
*/
void				clear(t_data *data);

#endif
