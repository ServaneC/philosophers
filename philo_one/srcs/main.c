/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/16 13:09:42 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			clean_end(t_idphilo *id[2], t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < 2)
	{
		if (pthread_join(g_thread[i], NULL))
			return (-1);
		pthread_mutex_unlock(&g_mutex[i]);
		pthread_mutex_destroy(&g_mutex[i]);
		free(id[i]);
	}
	free(philo);
	return (1);
}

int			main(int ac, char **av)
{
	t_philo		*philo;
	t_idphilo	*id[2];
	int			i;

	i = -1;
	if ((philo = init_philo(ac, av)) == NULL)
		return (0);
	while (++i < 2)
	{
		id[i] = init_idphilo(philo, i + 1);
		pthread_mutex_init(&g_mutex[i], NULL);
		if (pthread_create(&g_thread[i], NULL, philosophe_life, (void *)id[i]))
			return (-1);
	}
	return (clean_end(id, philo));
}
