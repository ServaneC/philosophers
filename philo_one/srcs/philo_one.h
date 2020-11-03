/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:35:57 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 18:27:22 by schene           ###   ########.fr       */
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

typedef unsigned long long t_u64;
struct s_id;

typedef struct			s_data
{
	t_u64				start;
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	struct s_id			*id;
	pthread_mutex_t		wr_right;
	pthread_mutex_t		death_mtx;
	pthread_mutex_t		*fork_m;
}						t_data;

typedef struct			s_id
{
	int					philo_id;
	t_u64				last_meal;
	t_data				*data;
	int					left_frk;
	int					right_frk;
	pthread_mutex_t		philo_mtx;
	pthread_mutex_t		eat_mtx;
}						t_id;

void					ft_putstr(char *str);
int						ft_strlen(char *str);
void					ft_putnbr(int nb);
int						ft_atoi(const char *str);
int						init_data(t_data *data, int ac, char **av);
int						timestamp_ms(t_u64 start);
t_u64					get_time_ms(void);
t_u64					get_time(void);
void					*philo_life(void *arg);
void					print_state(t_id *id, int action);
int						is_all_digit(char *str);
int						print_error(char *message1, int nb, char *message2);
int						check_av(int ac, char **av);

#endif
