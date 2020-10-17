/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/17 16:30:17 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	clean_end(t_idphilo **id, t_philo *philo, t_data *data)
{
	int		i;

	i = -1;
	while (++i < philo->nb_philo && id && data)
	{
		if (pthread_join(id[i]->data->threads[i], NULL))
			return (-1);
		pthread_mutex_unlock(&id[i]->data->mutex[i]);
		pthread_mutex_destroy(&id[i]->data->mutex[i]);
		free(id[i]);
	}
	free(philo);
	if (id)
		free(id);
	if (data)
	{
		free(data->forks);
		free(data->mutex);
		free(data->threads);
		free(data);
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_philo		*philo;
	t_data		*data;
	t_idphilo	**id;
	int			i;

	i = -1;
	if ((philo = init_philo(ac, av)) == NULL)
		return (0);
	if ((data = init_data(philo->nb_philo)) == NULL)
		return (clean_end(NULL, philo, NULL));
	if (!(id = malloc(sizeof(t_idphilo) * philo->nb_philo)))
		return (clean_end(NULL, philo, data));
	while (++i < philo->nb_philo)
	{
		if ((id[i] = init_idphilo(philo, i + 1, data)) == NULL)
			return (0);
		pthread_mutex_init(&data->mutex[i], NULL);
		if (pthread_create(&data->threads[i], NULL, philo_life, (void *)id[i]))
			return (-1);
	}
	return (clean_end(id, philo, data));
}
