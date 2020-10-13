/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:25:39 by schene            #+#    #+#             */
/*   Updated: 2020/10/13 13:26:11 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo		*init_philo(void)
{
	t_philo *philo;

	if (!(philo = malloc(sizeof(philo))))
		return (NULL);
	philo->nb_philo = 0;
	philo->time_die = 0;
	philo->time_eat = 0;
	philo->time_sleep = 0;
	philo->must_eat = -1;
	return (philo);
}

int			fill_philo(t_philo *philo, int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
	{
		ft_putstr("philo_one need 4 or 5 arguments !\n");
		return (0);
	}
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->must_eat = ft_atoi(av[5]);
	return (1);
}
