/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:25:39 by schene            #+#    #+#             */
/*   Updated: 2020/10/18 16:09:29 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			check_av(int ac, char **av)
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

t_data		*init_data(int nb_philo)
{
	t_data		*data;
	int			i;

	data = NULL;
	if (!(data = malloc(sizeof(*data))))
		return (NULL);
	if (!(data->threads = malloc(sizeof(*data->threads) * (nb_philo + 1))))
		return (NULL);
	if (!(data->mutex = malloc(sizeof(*data->mutex) * (nb_philo + 1))))
		return (NULL);
	if (!(data->forks = malloc(sizeof(*data->forks) * (nb_philo + 1))))
		return (NULL);
	i = -1;
	memset(&data->wr_right, 0, sizeof(data->wr_right));
	pthread_mutex_init(&data->wr_right, NULL);
	while (++i < nb_philo)
	{
		memset(&data->threads[i], 0, sizeof(data->threads));
		memset(&data->mutex[i], 0, sizeof(*data->mutex));
		memset(&data->forks[i], 0, sizeof(data->forks));
	}
	return (data);
}

t_philo		*init_philo(char **av)
{
	t_philo			*philo;

	philo = NULL;
	if (av[5] && (ft_atoi(av[5]) == 0))
		return (NULL);
	if (!(philo = malloc(sizeof(*philo))))
		return (NULL);
	memset(philo, 0, sizeof(*philo));
	philo->start = get_time_ms();
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]) * 1000;
	philo->time_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		philo->must_eat = ft_atoi(av[5]);
	return (philo);
}

t_id		*init_id(t_philo *philo, int id_philo, t_data *data)
{
	t_id	*id;

	id = NULL;
	if (!(id = malloc(sizeof(*id))))
		return (NULL);
	memset(id, 0, sizeof(*id));
	id->philo = philo;
	id->data = data;
	id->philo_id = id_philo;
	id->nb_meals = 0;
	id->left_frk = id_philo - 1;
	id->right_frk = id_philo - 2;
	if (id_philo == 1)
		id->right_frk = philo->nb_philo - 1;
	return (id);
}
