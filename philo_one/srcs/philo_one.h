/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:35:57 by schene            #+#    #+#             */
/*   Updated: 2020/10/16 13:46:15 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

int					g_death;

typedef unsigned long long t_u64;

typedef struct		s_philo
{
	t_u64			start_time;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
}					t_philo;

typedef struct		s_data
{
	pthread_t			threads[2];
	pthread_mutex_t		mutex[2];
	int					forks[2];
}					t_data;

typedef struct		s_idphilo
{
	t_philo			*philo;
	t_data			*data;
	int				philo_id;
}					t_idphilo;

void				ft_putstr(char *str);
int					ft_atoi(const char *str);
t_philo				*init_philo(int ac, char **av);
t_idphilo			*init_idphilo(t_philo *philo, int id, t_data *data);
t_data				*init_data(void);
int					timestamp_ms(t_u64 start_time);
t_u64				get_time_ms(void);
void				*philosophe_life(void *arg);

#endif
