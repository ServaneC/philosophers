/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:13:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/22 15:19:24 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void		taking_forks(t_id *id)
{
	while (forks < 2)
		;
	forks -= 1;
	sem_wait(id->data->sem);
	print_state(id, TAKE_FORK);
	forks -= 1;
	sem_wait(id->data->sem);
	print_state(id, TAKE_FORK);
}

static t_u64	philo_eat(t_id *id)
{
	t_u64		start_meal;

	start_meal = get_time_ms();
	print_state(id, EAT);
	usleep(id->data->time_eat);
	sem_post(id->data->sem);
	forks += 1;
	sem_post(id->data->sem);
	forks += 1;
	print_state(id, SLEEP);
	usleep(id->data->time_sleep);
	return (start_meal);
}

void			*philo_life(void *arg)
{
	t_id	*id;
	t_u64	last_meal;

	id = (t_id *)arg;
	last_meal = get_time_ms();
	while (timestamp_ms(last_meal) < id->data->time_die && !(g_death))
	{
		taking_forks(id);
		last_meal = philo_eat(id);
		if (++id->nb_meals == id->data->must_eat)
			return (NULL);
		print_state(id, THINK);
	}
	g_death++;
	return (print_state(id, DEAD));
}
