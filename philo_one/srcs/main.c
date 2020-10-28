/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 18:25:38 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		clean_end(t_data *data)
{
	int			i;

	i = -1;
	if (data->fork_m)
	{
		while (++i < data->nb_philo)
			pthread_mutex_destroy(&data->fork_m[i]);
		free(data->fork_m);
	}
	i = -1;
	if (data->id)
	{
		while (++i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->id[i].eat_mtx);
			pthread_mutex_destroy(&data->id[i].philo_mtx);
		}
		free(data->id);
	}
	pthread_mutex_destroy(&data->wr_right);
	pthread_mutex_destroy(&data->death_mtx);
	return (1);
}

static void		*monitor_count(void *arg)
{
	t_data	*data;
	int		i;
	int		total;

	data = (t_data*)arg;
	total = 0;
	while (total < data->must_eat)
	{
		i = -1;
		while (++i < data->nb_philo)
			pthread_mutex_lock(&data->id[i].eat_mtx);
		total++;
	}
	print_state(&data->id[0], END);
	pthread_mutex_unlock(&data->death_mtx);
	return ((void*)0);
}

static int		start_threads(t_data *data)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	data->start = get_time_ms();
	if (data->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void*)data) != 0)
			return (1);
		pthread_detach(tid);
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		philo = (void*)(&data->id[i]);
		if (pthread_create(&tid, NULL, &philo_life, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_data		data;

	if (init_data(&data, ac, av))
		return (clean_end(&data));
	if (start_threads(&data))
		return (clean_end(&data));
	pthread_mutex_lock(&data.death_mtx);
	pthread_mutex_unlock(&data.death_mtx);
	return (clean_end(&data));
}
