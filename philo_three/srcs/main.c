/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:56:35 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 18:42:09 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		clean_end(t_data *data)
{
	int		i;
	char	semaphore[250];

	if (data->id)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			sem_close(data->id[i].eat_sem);
			sem_close(data->id[i].philo_s);
			sem_name(SEM_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			sem_name(SEM_MUST_EAT, (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(data->id);
	}
	sem_close(data->forks_s);
	sem_close(data->wr_right);
	sem_close(data->death_s);
	sem_close(data->wr_dead);
	return (1);
}

static int		start_process(t_data *data)
{
	int			i;
	void		*philo;

	data->start = get_time_ms();
	i = -1;
	while (++i < data->nb_philo)
	{
		philo = (void*)(&data->id[i]);
		data->id[i].pid = fork();
		if (data->id[i].pid < 0)
			return (1);
		else if (data->id[i].pid == 0)
		{
			exec_philo(&data->id[i]);
			exit(0);
		}
		usleep(100);
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_data		data;
	int			i;

	if (check_av(ac, av))
		return (1);
	if (data_init(&data, ac, av)
		|| start_monitor_thread(&data)
		|| start_process(&data))
		return (clean_end(&data));
	sem_wait(data.death_s);
	i = -1;
	while (++i < data.nb_philo)
		kill(data.id[i].pid, SIGKILL);
	clean_end(&data);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WR);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_WR_DEATH);
	return (0);
}
