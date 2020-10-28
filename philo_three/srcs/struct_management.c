/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:08:03 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 14:27:17 by schene           ###   ########.fr       */
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

sem_t	*ft_sem_open(char const *name, int value)
{
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char	*make_semaphore_name(char const *base, char *buffer, int position)
{
	int	i;

	i = ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}

static int	init_sems(t_data *data)
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

static int	init_id(t_data *data)
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

int		data_init(t_data *data, int ac, char const **av)
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

// void			set_data(t_data *data, char **av, int nb_philo)
// {
// 	int		i;

// 	i = -1;
// 	sem_unlink("/wr_right");
// 	sem_unlink("/forks");
// 	sem_unlink("/death");
// 	data->wr_right = sem_open("/wr_right", O_CREAT | O_EXCL, 0600, 1);
// 	data->sem = sem_open("/forks", O_CREAT | O_EXCL, 0600, nb_philo);
// 	data->sem_death = sem_open("/death", O_CREAT | O_EXCL, 0600, 0);
// 	data->start = 0;
// 	data->nb_philo = nb_philo;
// 	data->time_die = ft_atoi(av[2]);
// 	data->time_eat = ft_atoi(av[3]) * 1000;
// 	data->time_sleep = ft_atoi(av[4]) * 1000;
// 	if (av[5])
// 		data->must_eat = ft_atoi(av[5]);
// }

// t_data			*init_data(int ac, char **av)
// {
// 	t_data		*data;
// 	int			nb_philo;

// 	data = NULL;
// 	if (!check_av(ac, av))
// 		return (NULL);
// 	nb_philo = ft_atoi(av[1]);
// 	if ((av[5] && (ft_atoi(av[5]) == 0)) || nb_philo < 2)
// 		return (NULL);
// 	if (!(data = malloc(sizeof(*data))))
// 		return (NULL);
// 	memset(data, 0, sizeof(*data));
// 	set_data(data, av, nb_philo);
// 	return (data);
// }

// t_id			*init_id(t_data *data, int id_philo)
// {
// 	t_id	*id;

// 	id = NULL;
// 	if (!(id = malloc(sizeof(*id))))
// 		return (NULL);
// 	memset(id, 0, sizeof(*id));
// 	id->data = data;
// 	id->philo_id = id_philo;
// 	sem_unlink("/sem_philo");
// 	id->sem_philo = sem_open("/sem_philo", O_CREAT | O_EXCL, 0600, 1);
// 	return (id);
// }
