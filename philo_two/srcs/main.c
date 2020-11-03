/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:09:50 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 19:17:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		clean_end(t_data *data)
{
	int		i;
	char	semaphore[250];

	if (data->id)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			sem_close(data->id[i].philo_s);
			sem_close(data->id[i].eat_sem);
			sem_name(SEM_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			sem_name(SEM_MUST_EAT, (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(data->id);
	}
	sem_close(data->wr_right);
	sem_close(data->death_s);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WR);
	sem_unlink(SEM_DEATH);
	return (1);
}

static void		*must_eat_count(void *arg)
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
			sem_wait(data->id[i].eat_sem);
		total++;
	}
	print_state(&data->id[0], END);
	sem_post(data->death_s);
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
		pthread_create(&tid, NULL, &must_eat_count, (void*)data);
		pthread_detach(tid);
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		philo = (void*)(&data->id[i]);
		pthread_create(&tid, NULL, &philo_life, (void*)philo);
		pthread_detach(tid);
		usleep(100);
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_data		data;

	if (check_av(ac, av))
		return (1);
	if (init_data(&data, av))
		return (clean_end(&data));
	if (start_threads(&data))
		return (clean_end(&data));
	sem_wait(data.death_s);
	return (clean_end(&data));
}
