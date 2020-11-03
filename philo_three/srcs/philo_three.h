/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:57:26 by schene            #+#    #+#             */
/*   Updated: 2020/10/29 08:53:18 by schene           ###   ########.fr       */
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

# define SEM_FORKS "/sem_forks"
# define SEM_WR "/wr_right"
# define SEM_DEATH "/death_sem"
# define SEM_WR_DEATH "/wr_dead"
# define SEM_PHILO "/philo_sem"
# define SEM_MUST_EAT "/eat_sem"

typedef unsigned long long t_u64;

struct s_id;

typedef struct		s_data
{
	int				nb_philo;
	t_u64			time_die;
	t_u64			time_eat;
	t_u64			time_sleep;
	int				must_eat;
	t_u64			start;
	struct s_id		*id;
	sem_t			*forks_s;
	sem_t			*wr_right;
	sem_t			*death_s;
	sem_t			*wr_dead;
}					t_data;

typedef struct		s_id
{
	pid_t			pid;
	int				philo_id;
	int				is_eating;
	t_u64			last_meal;
	t_data			*data;
	sem_t			*philo_s;
	sem_t			*eat_sem;
}					t_id;

void				ft_putstr(char *str);
int					ft_strlen(char *str);
void				ft_putnbr(int nb);
int					ft_atoi(const char *str);
int					timestamp_ms(t_u64 start);
int					ft_strcpy(char *dest, char *src);
t_u64				get_time_ms(void);
t_u64				get_time(void);
int					is_all_digit(char *str);
int					print_error(char *message1, int nb, char *message2);
void				print_state(t_id *id, int action);
int					data_init(t_data *data, int ac, char **av);
void				*philo_life(void *arg);
int					exec_philo(t_id *id);
char				*sem_name(char *base, char *buffer, int position);
void				*check_death(void *arg);
sem_t				*ft_sem_open(const char *name, int value);
int					start_monitor_thread(t_data *data);
int					check_av(int ac, char **av);
#endif
