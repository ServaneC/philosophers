/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:35:57 by schene            #+#    #+#             */
/*   Updated: 2020/10/23 10:55:02 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define TAKE_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define END 5

int					g_death;

typedef unsigned long long t_u64;

typedef struct		s_data
{
	t_u64				start;
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	pthread_mutex_t		wr_right;
	pthread_t			*threads;
	pthread_mutex_t		*mutex;
	int					*forks;
}					t_data;

typedef struct		s_id
{
	t_data			*data;
	int				nb_meals;
	int				philo_id;
	int				left_frk;
	int				right_frk;
}					t_id;

void				ft_putstr(char *str);
int					ft_strlen(char *str);
void				ft_putnbr(int nb);
int					ft_atoi(const char *str);
t_data				*init_data(int ac, char **av);
t_id				*init_id(t_data *data, int id);
int					timestamp_ms(t_u64 start);
t_u64				get_time_ms(void);
void				*philo_life(void *arg);
void				*print_state(t_id *id, int action);
int					is_all_digit(char *str);
int					print_error(void);

#endif
