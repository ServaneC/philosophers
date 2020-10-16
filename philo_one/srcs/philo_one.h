/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:35:57 by schene            #+#    #+#             */
/*   Updated: 2020/10/15 14:48:50 by schene           ###   ########.fr       */
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

static pthread_t			philosophers[2];
static pthread_mutex_t		mutex_forks[2];
static int					forks[2];

typedef struct		s_philo
{
	int				philo_id;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
}					t_philo;

void				ft_putstr(char *str);
int					ft_atoi(const char *str);
t_philo				*init_philo(int ac, char **av);
int					fill_philo(t_philo *philo, int ac, char **av);

#endif
