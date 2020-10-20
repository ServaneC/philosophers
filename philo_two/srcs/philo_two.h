/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:35:46 by schene            #+#    #+#             */
/*   Updated: 2020/10/20 10:59:46 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>

typedef unsigned long long t_u64;

typedef struct		s_options
{
	t_u64			start;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
}					t_options;

void				ft_putstr(char *str);
int					ft_strlen(char *str);
void				ft_putnbr(int nb);
int					ft_atoi(const char *str);
int					timestamp_ms(t_u64 start);
t_u64				get_time_ms(void);
int					is_all_digit(char *str);
int					print_error(void);

#endif
