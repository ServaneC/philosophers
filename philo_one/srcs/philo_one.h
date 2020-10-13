/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:35:57 by schene            #+#    #+#             */
/*   Updated: 2020/10/13 13:28:20 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_philo
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat;
}				t_philo;

void			ft_putstr(char *str);
int				ft_atoi(const char *str);
t_philo			*init_philo(void);
int				fill_philo(t_philo *philo, int ac, char **av);

#endif
