/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:08:03 by schene            #+#    #+#             */
/*   Updated: 2020/10/27 13:52:34 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void			set_data(t_data *data, char **av, int nb_philo)
{
	int		i;

	i = -1;
	sem_unlink("/wr_right");
	sem_unlink("/forks");
	sem_unlink("/death");
	data->wr_right = sem_open("/wr_right", O_CREAT | O_EXCL, 0600, 1);
	data->sem = sem_open("/forks", O_CREAT | O_EXCL, 0600, nb_philo);
	data->sem_death = sem_open("/death", O_CREAT | O_EXCL, 0600, 0);
	data->start = 0;
	data->nb_philo = nb_philo;
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

	data = NULL;
	if (!check_av(ac, av))
		return (NULL);
	nb_philo = ft_atoi(av[1]);
	if ((av[5] && (ft_atoi(av[5]) == 0)) || nb_philo < 2)
		return (NULL);
	if (!(data = malloc(sizeof(*data))))
		return (NULL);
	memset(data, 0, sizeof(*data));
	set_data(data, av, nb_philo);
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
	id->thread = 0;
	return (id);
}
