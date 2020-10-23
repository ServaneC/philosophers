/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:13:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/23 12:46:51 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		taking_forks(t_id *id)
{
	id->data->forks[id->right_frk] = 1;
	id->data->forks[id->left_frk] = 1;
	pthread_mutex_lock(&id->data->mutex[id->right_frk]);
	pthread_mutex_lock(&id->data->mutex[id->left_frk]);
	print_state(id, TAKE_FORK);
	print_state(id, TAKE_FORK);
}

static t_u64	philo_eat(t_id *id)
{
	t_u64		start_meal;

	start_meal = get_time_ms();
	print_state(id, EAT);
	usleep(id->data->time_eat);
	id->data->forks[id->right_frk] = 0;
	pthread_mutex_unlock(&id->data->mutex[id->right_frk]);
	id->data->forks[id->left_frk] = 0;
	pthread_mutex_unlock(&id->data->mutex[id->left_frk]);
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
		if (!id->data->forks[id->right_frk] && !id->data->forks[id->left_frk])
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
