/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/16 13:44:33 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			clean_end(t_idphilo *id[2], t_philo *philo, t_data *data)
{
	int		i;

	i = -1;
	while (++i < 2)
	{
		if (pthread_join(id[i]->data->threads[i], NULL))
			return (-1);
		pthread_mutex_unlock(&id[i]->data->mutex[i]);
		pthread_mutex_destroy(&id[i]->data->mutex[i]);
		free(id[i]);
	}
	free(philo);
	free(data);
	return (1);
}

int			main(int ac, char **av)
{
	t_philo		*philo;
	t_data		*data;
	t_idphilo	*id[2];
	int			i;

	i = -1;
	if ((philo = init_philo(ac, av)) == NULL)
		return (0);
	if ((data = init_data()) == NULL)
		return (0);
	while (++i < 2)
	{
		if ((id[i] = init_idphilo(philo, i + 1, data)) == NULL)
			return (0);
		pthread_mutex_init(&data->mutex[i], NULL);
		if (pthread_create(&data->threads[i], NULL, philosophe_life, (void *)id[i]))
			return (-1);
	}
	return (clean_end(id, philo, data));
}
