/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:25:39 by schene            #+#    #+#             */
/*   Updated: 2020/10/20 11:22:16 by schene           ###   ########.fr       */
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
	return (1);
}

void			set_data(t_data *data, char **av)
{
	int		i;

	i = -1;
	memset(&data->wr_right, 0, sizeof(data->wr_right));
	pthread_mutex_init(&data->wr_right, NULL);
	while (++i < ft_atoi(av[1]))
	{
		memset(&data->threads[i], 0, sizeof(data->threads));
		memset(&data->mutex[i], 0, sizeof(*data->mutex));
		memset(&data->forks[i], 0, sizeof(data->forks));
		pthread_mutex_init(&data->mutex[i], NULL);
	}
	data->start = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
}

t_data			*init_data(int ac, char **av)
{
	t_data		*data;
	int			nb_philo;

	nb_philo = ft_atoi(av[1]);
	data = NULL;
	if (!check_av(ac, av))
		return (NULL);
	if (av[5] && (ft_atoi(av[5]) == 0))
		return (NULL);
	else if (ft_atoi(av[1]) < 2)
		return (NULL);
	if (!(data = malloc(sizeof(*data))))
		return (NULL);
	memset(data, 0, sizeof(*data));
	if (!(data->threads = malloc(sizeof(*data->threads) * (nb_philo + 1))))
		return (NULL);
	if (!(data->mutex = malloc(sizeof(*data->mutex) * (nb_philo + 1))))
		return (NULL);
	if (!(data->forks = malloc(sizeof(*data->forks) * (nb_philo + 1))))
		return (NULL);
	set_data(data, av);
	return (data);
}

t_id			*init_id(t_data *data, int id_philo)
{
	t_id	*id;

	id = NULL;
	if (!(id = malloc(sizeof(*id))))
		return (NULL);
	memset(id, 0, sizeof(*id));
	id->data = data;
	id->philo_id = id_philo;
	id->nb_meals = 0;
	id->left_frk = id_philo - 1;
	id->right_frk = id_philo - 2;
	if (id_philo == 1)
		id->right_frk = data->nb_philo - 1;
	return (id);
}
