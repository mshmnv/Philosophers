/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:51:12 by lbagg             #+#    #+#             */
/*   Updated: 2021/02/15 19:37:32 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

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
	int				state;
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
	sem_t			*forks;
	int				forks_left;
	sem_t			*die_lock;
	sem_t			*write_lock;
	int				someone_dead;
}					t_data;

/*
** main.c
*/
t_philo				*init_philos(t_data *data);
t_data				*init_data(char **argv);
int					check_args(int argc, char **argv);
/*
** utils.c
*/
int					ft_atoi(const char *nptr);
void				display(t_philo *philo, char *msg);
int					time_now();
int					error(int er_num);
/*
** clear.c
*/
void				clear(t_data *data);

#endif