/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:25:39 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 18:20:00 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		check_av(int ac, char **av)
{
	int	i;

	i = 0;
	if (!(ac == 5 || ac == 6))
		return (print_error());
	while (av[++i])
	{
		if (!is_all_digit(av[i]))
			return (print_error());
	}
	return (0);
}

static int		init_mutex(t_data *data)
{
	int		i;

	pthread_mutex_init(&data->death_mtx, NULL);
	pthread_mutex_init(&data->wr_right, NULL);
	pthread_mutex_lock(&data->death_mtx);
	if (!(data->fork_m =
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->nb_philo)))
		return (1);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->fork_m[i], NULL);
	return (0);
}

static void		init_id(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->id[i].is_eating = 0;
		data->id[i].philo_id = i;
		data->id[i].left_frk = i;
		data->id[i].right_frk = (i + 1) % data->nb_philo;
		data->id[i].nb_meals = 0;
		data->id[i].data = data;
		pthread_mutex_init(&data->id[i].philo_mtx, NULL);
		pthread_mutex_init(&data->id[i].eat_mtx, NULL);
		pthread_mutex_lock(&data->id[i].eat_mtx);
	}
}

int				init_data(t_data *data, int ac, char **av)
{
	if (check_av(ac, av))
		return (1);
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->must_eat = 0;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	if (data->nb_philo < 2 || data->nb_philo > 200 || data->time_die < 60
		|| data->time_eat < 60 || data->time_sleep < 60
		|| data->must_eat < 0)
		return (1);
	data->time_eat *= 1000;
	data->time_sleep *= 1000;
	data->fork_m = NULL;
	data->id = NULL;
	if (!(data->id = (t_id *)malloc(sizeof(*(data->id)) * data->nb_philo)))
		return (1);
	init_id(data);
	return (init_mutex(data));
}
