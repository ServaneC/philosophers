/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:35:46 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 19:12:21 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define TAKE_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define END 5

# define SEM_FORKS "/sem_forks"
# define SEM_WR "/wr_right"
# define SEM_DEATH "/death_sem"
# define SEM_PHILO "/philo_sem"
# define SEM_MUST_EAT "/eat_sem"

typedef unsigned long long t_u64;
struct s_id;

typedef struct		s_data
{
	t_u64			start;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	struct s_id		*id;
	sem_t			*forks_s;
	sem_t			*wr_right;
	sem_t			*death_s;
}					t_data;

typedef struct		s_id
{
	int				philo_id;
	int				is_eating;
	t_u64			last_meal;
	t_u64			limit;
	t_data			*data;
	int				nb_meals;
	sem_t			*philo_s;
	sem_t			*eat_sem;
}					t_id;

void				ft_putstr(char *str);
int					ft_strlen(char *str);
void				ft_putnbr(int nb);
int					ft_atoi(const char *str);
int					ft_strcpy(char *dest, char *src);
int					timestamp_ms(t_u64 start);
t_u64				get_time_ms(void);
t_u64				get_time(void);
int					is_all_digit(char *str);
int					print_error(void);
int					init_data(t_data *data, int ac, char **av);
void				print_state(t_id *id, int action);
sem_t				*ft_sem_open(char const *name, int value);
char				*sem_name(char *base, char *buffer, int position);
void				*philo_life(void *arg);

#endif
