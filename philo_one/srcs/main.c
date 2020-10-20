/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/20 11:06:35 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	clean_end(t_id **id_tab, t_data *data)
{
	int			i;

	i = -1;
	pthread_mutex_destroy(&data->wr_right);
	while (++i < data->nb_philo && id_tab)
	{
		pthread_mutex_destroy(&id_tab[i]->data->mutex[i]);
		free(id_tab[i]);
	}
	free(data->forks);
	free(data->mutex);
	free(data->threads);
	free(data);
	if (id_tab)
		free(id_tab);
	return (1);
}

static int	th_start_join(t_id **id_tab)
{
	int		i;

	i = -1;
	while (++i < id_tab[0]->data->nb_philo)
		pthread_create(&id_tab[i]->data->threads[i], NULL,
			philo_life, id_tab[i]);
	i = -1;
	while (++i < id_tab[0]->data->nb_philo)
		pthread_join(id_tab[i]->data->threads[i], NULL);
	if (!g_death)
		print_state(id_tab[0], END);
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
	th_start_join(id_tab);
	return (clean_end(id_tab, data));
}
