/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:56:36 by schene            #+#    #+#             */
/*   Updated: 2020/10/29 09:00:03 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_death(void *arg)
{
	t_id		*id;

	id = (t_id *)arg;
	while (1)
	{
		if (!id->is_eating && (get_time() >
			(id->last_meal + id->data->time_die)))
		{
			print_state(id, DEAD);
			sem_post(id->data->death_s);
			return ((void*)0);
		}
		usleep(1000);
	}
}

void	*must_eat_count(void *arg)
{
	t_data	*data;
	int		total;
	int		i;

	data = (t_data*)arg;
	total = 0;
	while (total < data->must_eat)
	{
		i = -1;
		while (++i < data->nb_philo)
			sem_wait(data->id[i].eat_sem);
		total++;
	}
	print_state(&data->id[0], END);
	sem_post(data->death_s);
	return ((void*)0);
}

int		start_monitor_thread(t_data *data)
{
	pthread_t	tid;

	if (data->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &must_eat_count, (void*)data) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}
