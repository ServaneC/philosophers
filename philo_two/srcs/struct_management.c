/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:43:04 by schene            #+#    #+#             */
/*   Updated: 2020/10/20 10:48:04 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		check_av(int ac, char **av)
{
	int	i;

	i = 0;
	if (!(ac == 5 || ac == 6))
		return (print_error());
	while (av[++i])
	{
		if (!is_all_digit(av[i]))
			return (print_error());
	}
	return (1);
}

t_options		*init_options(int ac, char **av)
{
	t_options	*options;

	options = NULL;
	if (!check_av(ac, av))
		return (NULL);
	if (av[5] && (ft_atoi(av[5]) == 0))
		return (NULL);
	else if (ft_atoi(av[1]) < 2)
		return (NULL);
	if (!(options = malloc(sizeof(*options))))
		return (NULL);
	memset(options, 0, sizeof(*options));
	options->start = 0;
	options->nb_philo = ft_atoi(av[1]);
	options->time_die = ft_atoi(av[2]);
	options->time_eat = ft_atoi(av[3]) * 1000;
	options->time_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		options->must_eat = ft_atoi(av[5]);
	return (options);
}