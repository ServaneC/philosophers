/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:56:35 by schene            #+#    #+#             */
/*   Updated: 2020/10/26 13:27:11 by schene           ###   ########.fr       */
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
	while (++i < data->nb_philo && id_tab)
		free(id_tab[i]);
	free(data->threads);
	free(data);
	if (id_tab)
		free(id_tab);
	return (1);
}

static int	fork_and_wait(t_id **id_tab, int nb_philo)
{
	pid_t	pids[nb_philo];
	int		i;

	i = -1;
	while (++i < nb_philo)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (clean_end(id_tab, id_tab[0]->data));
		else if (pids[i] == 0)
		{
			philo_life(id_tab[i]);
			if (!g_death)
				print_state(id_tab[0], END);
		}
	}
	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < nb_philo)
		kill (pids[i], SIGTERM);
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
	fork_and_wait(id_tab, data->nb_philo);
	return (clean_end(id_tab, data));
}