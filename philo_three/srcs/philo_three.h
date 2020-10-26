/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:57:26 by schene            #+#    #+#             */
/*   Updated: 2020/10/26 13:16:51 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>


# define TAKE_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define END 5

int					g_death;
int					g_forks;

typedef unsigned long long t_u64;

typedef struct		s_data
{
	t_u64			start;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	sem_t			*wr_right;
	sem_t			*sem;
	pthread_t		*threads;
}					t_data;

typedef struct		s_id
{
	t_data			*data;
	int				nb_meals;
	int				philo_id;
}					t_id;

void				ft_putstr(char *str);
int					ft_strlen(char *str);
void				ft_putnbr(int nb);
int					ft_atoi(const char *str);
int					timestamp_ms(t_u64 start);
t_u64				get_time_ms(void);
int					is_all_digit(char *str);
int					print_error(void);
void				*print_state(t_id *id, int action);
t_data				*init_data(int ac, char **av);
t_id				*init_id(t_data *data, int id_philo);
void				*philo_life(t_id *id);

#endif