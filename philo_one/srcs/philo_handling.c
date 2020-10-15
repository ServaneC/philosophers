/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:25:39 by schene            #+#    #+#             */
/*   Updated: 2020/10/15 11:44:47 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo		*init_philo(int ac, char **av)
{
	t_philo *philo;

	memset(forks, 0, 2);
	if (!(ac == 5 || ac == 6))
	{
		ft_putstr("philo_one need 4 or 5 arguments !\n");
		return (NULL);
	}
	if (!(philo = malloc(sizeof(philo))))
		return (NULL);
	philo->philo_id = 0;
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->must_eat = ft_atoi(av[5]);
	return (philo);
}
