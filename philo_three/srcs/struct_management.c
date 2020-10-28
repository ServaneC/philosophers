/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:08:03 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 15:10:55 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		check_av(int ac, const char **av)
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

static int		init_sems(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WR);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_WR_DEATH);
	if ((data->forks_s = ft_sem_open(SEM_FORKS, data->nb_philo)) < 0
		|| (data->wr_right = ft_sem_open(SEM_WR, 1)) < 0
		|| (data->death_s = ft_sem_open(SEM_DEATH, 0)) < 0
		|| (data->wr_dead = ft_sem_open(SEM_WR_DEATH, 1)) < 0)
		return (1);
	return (0);
}

static int		init_id(t_data *data)
{
	int		i;
	char	semaphore[250];

	i = 0;
	while (i < data->nb_philo)
	{
		data->id[i].is_eating = 0;
		data->id[i].philo_id = i;
		data->id[i].data = data;
		make_semaphore_name(SEM_PHILO, (char*)semaphore, i);
		sem_unlink(semaphore);
		if ((data->id[i].philo_s = ft_sem_open(semaphore, 1)) < 0)
			return (1);
		make_semaphore_name(SEM_MUST_EAT, (char*)semaphore, i);
		sem_unlink(semaphore);
		if ((data->id[i].must_eat_s = ft_sem_open(semaphore, 0)) < 0)
			return (1);
		i++;
	}
	return (0);
}

int				data_init(t_data *data, int ac, char const **av)
{
	if (!check_av(ac, av))
		return (1);
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->must_eat = 0;
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	if (data->nb_philo < 2 || data->nb_philo > 200 || data->time_die < 60
		|| data->time_eat < 60 || data->time_sleep < 60
		|| data->must_eat < 0)
		return (1);
	data->time_eat *= 1000;
	data->time_sleep *= 1000;
	data->forks_s = NULL;
	data->id = NULL;
	if (!(data->id = (t_id *)malloc(sizeof(*(data->id)) * data->nb_philo)))
		return (1);
	if (init_id(data))
		return (1);
	return (init_sems(data));
}
