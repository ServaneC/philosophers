/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:13:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/29 08:50:29 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void		taking_forks(t_id *id)
{
	sem_wait(id->data->forks_s);
	print_state(id, TAKE_FORK);
	sem_wait(id->data->forks_s);
	print_state(id, TAKE_FORK);
}

static void		philo_eat(t_id *id)
{
	sem_wait(id->philo_s);
	id->is_eating = 1;
	id->last_meal = get_time();
	print_state(id, EAT);
	usleep(id->data->time_eat);
	id->nb_meals++;
	id->is_eating = 0;
	sem_post(id->philo_s);
	sem_post(id->eat_sem);
}

static void		philo_sleep(t_id *id)
{
	print_state(id, SLEEP);
	sem_post(id->data->forks_s);
	sem_post(id->data->forks_s);
	usleep(id->data->time_sleep);
}

void			*monitor(void *arg)
{
	t_id		*id;

	id = (t_id *)arg;
	while (1)
	{
		sem_wait(id->philo_s);
		if (!id->is_eating && get_time() > (id->last_meal + id->data->time_die))
		{
			print_state(id, DEAD);
			sem_post(id->philo_s);
			sem_post(id->data->death_s);
			return ((void*)0);
		}
		sem_post(id->philo_s);
		usleep(1000);
	}
}

void			*philo_life(void *arg)
{
	pthread_t	thread;
	t_id		*id;

	id = (t_id *)arg;
	id->last_meal = get_time();
	if (pthread_create(&thread, NULL, &monitor, arg) != 0)
		return ((void *)1);
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
