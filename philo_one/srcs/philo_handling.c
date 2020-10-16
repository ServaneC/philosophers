/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:25:39 by schene            #+#    #+#             */
/*   Updated: 2020/10/16 12:46:15 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo		*init_philo(int ac, char **av)
{
	t_philo			*philo;

	philo = NULL;
	if (!(ac == 5 || ac == 6))
	{
		ft_putstr("philo_one need 4 or 5 arguments !\n");
		return (NULL);
	}
	if (!(philo = malloc(sizeof(*philo))))
		return (NULL);
	memset(philo, 0, sizeof(*philo));
	philo->start_time = get_time_ms();
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]) * 1000;
	philo->time_sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		philo->must_eat = ft_atoi(av[5]);
	return (philo);
}

t_idphilo	*init_idphilo(t_philo *philo, int id)
{
	t_idphilo	*idphilo;

	idphilo = NULL;
	if (!(idphilo = malloc(sizeof(*idphilo))))
		return (NULL);
	memset(idphilo, 0, sizeof(*idphilo));
	idphilo->philo = philo;
	idphilo->philo_id = id;
	return (idphilo);
}
