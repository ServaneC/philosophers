/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:56:35 by schene            #+#    #+#             */
/*   Updated: 2020/10/26 15:54:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	clean_end(t_data *data)
{
	int			i;

	i = -1;
	sem_close(data->wr_right);
	sem_unlink("/wr_right");
	sem_close(data->sem);
	sem_unlink("/forks");
	free(data);
	return (1);
}

static int	fork_and_wait(t_data *data)
{
	pid_t	pids[data->nb_philo];
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (clean_end(data));
		else if (pids[i] == 0)
		{
			philo_life(data, i);
			if (!g_death)
				print_state(data, i, END);
		}
	}
	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < data->nb_philo)
		kill(pids[i], SIGTERM);
	return (clean_end(data));
}

int			main(int ac, char **av)
{
	t_data		*data;
	int			i;

	i = -1;
	if ((data = init_data(ac, av)) == NULL)
		return (0);
	data->start = get_time_ms();
	fork_and_wait(data);
	return (1);
}
