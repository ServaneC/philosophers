/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:56:35 by schene            #+#    #+#             */
/*   Updated: 2020/10/27 13:50:39 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	clean_end(t_id **id_tab, t_data *data)
{
	int			i;

	i = -1;
	sem_close(data->wr_right);
	sem_unlink("/wr_right");
	sem_close(data->sem);
	sem_unlink("/forks");
	sem_close(data->sem_death);
	while (++i < data->nb_philo && id_tab)
		free(id_tab[i]);
	free(data);
	if (id_tab)
		free(id_tab);
	return (1);
}

static int	fork_and_wait(t_id **id_tab, t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		id_tab[i]->pid = fork();
		if (id_tab[i]->pid == -1)
			return (clean_end(id_tab, data));
		else if (id_tab[i]->pid == 0)
		{
			exec_philo(id_tab[i]);
			exit(0);
		}
		usleep(100);
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_data		*data;
	t_id		**id_tab;
	int			i;

	i = -1;
	if ((data = init_data(ac, av)) == NULL)
		return (0);
	if (!(id_tab = malloc(sizeof(t_id) * data->nb_philo)))
		return (clean_end(NULL, data));
	while (++i < data->nb_philo)
		if ((id_tab[i] = init_id(data, i + 1)) == NULL)
			return (clean_end(id_tab, data));
	data->start = get_time_ms();
	fork_and_wait(id_tab, data);
	sem_wait(data->sem_death);
	i = -1;
	while (++i < data->nb_philo)
		kill(id_tab[i]->pid, SIGKILL);
	return (clean_end(id_tab, data));
}
