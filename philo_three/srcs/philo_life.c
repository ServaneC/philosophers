/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:25:45 by schene            #+#    #+#             */
/*   Updated: 2020/10/26 13:20:58 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		taking_forks(t_id *id)
{
	g_forks -= 2;
	sem_wait(id->data->sem);
	sem_wait(id->data->sem);
	print_state(id, TAKE_FORK);
	print_state(id, TAKE_FORK);
}

static t_u64	philo_eat(t_id *id)
{
	t_u64		start_meal;

	start_meal = get_time_ms();
	print_state(id, EAT);
	usleep(id->data->time_eat);
	g_forks += 2;
	sem_post(id->data->sem);
	sem_post(id->data->sem);
	print_state(id, SLEEP);
	usleep(id->data->time_sleep);
	return (start_meal);
}

void			*philo_life(t_id *id)
{
	t_u64	last_meal;

	last_meal = get_time_ms();
	while (timestamp_ms(last_meal) < id->data->time_die && !(g_death))
	{
		if (g_forks >= 2)
		{
			taking_forks(id);
			last_meal = philo_eat(id);
			if (++id->nb_meals == id->data->must_eat)
				return (NULL);
			print_state(id, THINK);
		}
	}
	return (print_state(id, DEAD));
}
