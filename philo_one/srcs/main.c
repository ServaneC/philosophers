/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/19 14:36:49 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	clean_end(t_id **id_tab, t_philo *philo, t_data *data)
{
	int			i;

	i = -1;
	pthread_mutex_destroy(&data->wr_right);
	while (++i < philo->nb_philo && id_tab && data)
	{
		pthread_mutex_destroy(&id_tab[i]->data->mutex[i]);
		free(id_tab[i]);
	}
	free(philo);
	if (id_tab)
		free(id_tab);
	if (data)
	{
		free(data->forks);
		free(data->mutex);
		free(data->threads);
		free(data);
	}
	return (1);
}

static void	join_thread(t_id **id_tab)
{
	int		i;

	i = -1;
	while (++i < id_tab[0]->philo->nb_philo)
		pthread_join(id_tab[i]->data->threads[i], NULL);
	if (!g_death)
		print_state(id_tab[0], END);
}

static int	start_thread(t_id **id_tab)
{
	int		i;

	i = -1;
	while (++i < id_tab[0]->philo->nb_philo)
		pthread_create(&id_tab[i]->data->threads[i], NULL,
			philo_life, id_tab[i]);
	return (1);
}

int			main(int ac, char **av)
{
	t_philo		*philo;
	t_data		*data;
	t_id		**id_tab;
	int			i;

	i = -1;
	if ((philo = init_philo(ac, av)) == NULL)
		return (0);
	if ((data = init_data(philo->nb_philo)) == NULL)
		return (clean_end(NULL, philo, NULL));
	if (!(id_tab = malloc(sizeof(t_id) * philo->nb_philo)))
		return (clean_end(NULL, philo, data));
	while (++i < philo->nb_philo)
		if ((id_tab[i] = init_id(philo, i + 1, data)) == NULL)
			return (clean_end(id_tab, philo, data));
	philo->start = get_time_ms();
	start_thread(id_tab);
	join_thread(id_tab);
	return (clean_end(id_tab, philo, data));
}
