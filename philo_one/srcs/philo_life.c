/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:13:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/17 18:29:07 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		taking_forks(t_id *id, int time_passed)
{
	id->data->forks[id->right_frk] = 1;
	pthread_mutex_lock(&id->data->mutex[id->right_frk]);
	if (time_passed <= id->philo->time_die && !(g_death))
	{
		print_state(timestamp_ms(id->philo->start), id->philo_id, TAKE_FORK);
		id->data->forks[id->left_frk] = 1;
		pthread_mutex_lock(&id->data->mutex[id->left_frk]);
	}
	if (time_passed <= id->philo->time_die && !(g_death))
		print_state(timestamp_ms(id->philo->start), id->philo_id, TAKE_FORK);
}

static t_u64	philo_eat(t_id *id, int time_passed)
{
	t_u64		start_meal;

	start_meal = get_time_ms();
	(void)time_passed;
	if (time_passed <= id->philo->time_die && !(g_death))
	{
		print_state(timestamp_ms(id->philo->start), id->philo_id, EAT);
		usleep(id->philo->time_eat);
	}
	pthread_mutex_unlock(&id->data->mutex[id->right_frk]);
	pthread_mutex_unlock(&id->data->mutex[id->left_frk]);
	id->data->forks[id->right_frk] = 0;
	id->data->forks[id->left_frk] = 0;
	return (start_meal);
}

static void		philo_sleep(t_id *id, int time_passed)
{
	if (time_passed <= id->philo->time_die && !(g_death))
	{
		print_state(timestamp_ms(id->philo->start), id->philo_id, SLEEP);
		usleep(id->philo->time_sleep);
	}
}

static void		philo_think(t_id *id, int time_passed)
{
	if (time_passed <= id->philo->time_die && !(g_death))
		print_state(timestamp_ms(id->philo->start), id->philo_id, THINK);
}

void			*philo_life(void *arg)
{
	t_id	*id;
	t_u64	last_meal;
	int		time_passed;

	id = (t_id *)arg;
	last_meal = get_time_ms();
	time_passed = 0;
	while (time_passed <= id->philo->time_die && !(g_death))
	{
		if (id->data->forks[id->right_frk] == 0 &&
			id->data->forks[id->left_frk] == 0)
		{
			taking_forks(id, timestamp_ms(last_meal));
			last_meal = philo_eat(id, timestamp_ms(last_meal));
			philo_sleep(id, timestamp_ms(last_meal));
			philo_think(id, timestamp_ms(last_meal));
		}
		time_passed = timestamp_ms(last_meal);
	}
	if (!g_death)
	{
		g_death++;
		print_state(timestamp_ms(id->philo->start), id->philo_id, DEAD);
	}
	return (NULL);
}
