/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:08:03 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 18:42:09 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				check_av(int ac, char **av)
{
	int	i;

	i = 0;
	if (!(ac == 5 || ac == 6))
		return (print_error("number of arguments = ", ac, " (must be 5 or 6)"));
	while (av[++i])
	{
		if (!is_all_digit(av[i]))
			return (print_error("argument number ", i, " is not only digit"));
	}
	if (ft_atoi(av[1]) < 2)
	{
		return (print_error("the number ", ft_atoi(av[1]),
			" is not a valid number of philosophers"));
	}
	return (0);
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

	i = -1;
	while (++i < data->nb_philo)
	{
		data->id[i].is_eating = 0;
		data->id[i].philo_id = i;
		data->id[i].data = data;
		data->id[i].nb_meals = 0;
		sem_name(SEM_PHILO, (char*)semaphore, i);
		sem_unlink(semaphore);
		if ((data->id[i].philo_s = ft_sem_open(semaphore, 1)) < 0)
			return (1);
		sem_name(SEM_MUST_EAT, (char*)semaphore, i);
		sem_unlink(semaphore);
		if ((data->id[i].eat_sem = ft_sem_open(semaphore, 0)) < 0)
			return (1);
	}
	return (0);
}

int				data_init(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->must_eat = 0;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
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
