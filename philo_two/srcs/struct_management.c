/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:43:04 by schene            #+#    #+#             */
/*   Updated: 2020/10/20 13:33:41 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	memset(&data->wr_right, 0, sizeof(data->wr_right));
	data->wr_right = sem_open("/wr_right", O_CREAT, O_RDWR, 1);
	data->sem = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR, nb_philo);
	while (++i < nb_philo)
		memset(&data->threads[i], 0, sizeof(data->threads[i]));
	data->start = 0;
	data->nb_philo = nb_philo;
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	data->forks = nb_philo;
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
	if (!(data->wr_right = malloc(sizeof(*data->wr_right))))
		return (NULL);	
	if (!(data->sem = malloc(sizeof(*data->sem))))
		return (NULL);
	memset(data, 0, sizeof(*data));
	if (!(data->threads = malloc(sizeof(*data->threads) * (nb_philo + 1))))
		return (NULL);	
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
	id->nb_meals = 0;
	return (id);
}