/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:25:45 by schene            #+#    #+#             */
/*   Updated: 2020/10/26 15:47:25 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		taking_forks(t_data *data, int philo_id)
{
	g_forks -= 2;
	sem_wait(data->sem);
	sem_wait(data->sem);
	print_state(data, philo_id, TAKE_FORK);
	print_state(data, philo_id, TAKE_FORK);
}

static t_u64	philo_eat(t_data *data, int philo_id)
{
	t_u64		start_meal;

	start_meal = get_time_ms();
	print_state(data, philo_id, EAT);
	usleep(data->time_eat);
	g_forks += 2;
	sem_post(data->sem);
	sem_post(data->sem);
	print_state(data, philo_id, SLEEP);
	usleep(data->time_sleep);
	return (start_meal);
}

void			*philo_life(t_data *data, int philo_id)
{
	t_u64	last_meal;
	int		nb_meals;

	nb_meals = 0;
	last_meal = data->start;
	while (timestamp_ms(last_meal) < data->time_die && !(g_death))
	{
		if (g_forks >= 2)
		{
			taking_forks(data, philo_id);
			last_meal = philo_eat(data, philo_id);
			if (++nb_meals == data->must_eat)
				return (NULL);
			print_state(data, philo_id, THINK);
		}
	}
	return (print_state(data, philo_id, DEAD));
}
