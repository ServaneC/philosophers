/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:13:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 18:27:04 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		taking_forks(t_id *id)
{
	pthread_mutex_lock(&id->data->fork_m[id->left_frk]);
	print_state(id, TAKE_FORK);
	pthread_mutex_lock(&id->data->fork_m[id->right_frk]);
	print_state(id, TAKE_FORK);
}

static void		philo_eat(t_id *id)
{
	pthread_mutex_lock(&id->philo_mtx);
	id->is_eating = 1;
	id->last_meal = get_time();
	print_state(id, EAT);
	usleep(id->data->time_eat);
	id->nb_meals++;
	id->is_eating = 0;
	pthread_mutex_unlock(&id->philo_mtx);
	pthread_mutex_unlock(&id->eat_mtx);
}

static void		philo_sleep(t_id *id)
{
	print_state(id, SLEEP);
	pthread_mutex_unlock(&id->data->fork_m[id->left_frk]);
	pthread_mutex_unlock(&id->data->fork_m[id->right_frk]);
	usleep(id->data->time_sleep);
}

void			*monitor(void *arg)
{
	t_id		*id;

	id = (t_id *)arg;
	while (1)
	{
		pthread_mutex_lock(&id->philo_mtx);
		if (!id->is_eating && get_time() > (id->last_meal + id->data->time_die))
		{
			print_state(id, DEAD);
			pthread_mutex_unlock(&id->philo_mtx);
			pthread_mutex_unlock(&id->data->death_mtx);
			return ((void*)0);
		}
		pthread_mutex_unlock(&id->philo_mtx);
		usleep(1000);
	}
}

void			*philo_life(void *arg)
{
	t_id		*id;
	pthread_t	thread;

	id = (t_id *)arg;
	id->last_meal = get_time();
	thread = 0;
	if (pthread_create(&thread, NULL, &monitor, arg) != 0)
		return ((void*)1);
	pthread_detach(thread);
	while (1)
	{
		taking_forks(id);
		philo_eat(id);
		philo_sleep(id);
		print_state(id, THINK);
	}
	return ((void *)0);
}
