/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:25:45 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 18:02:36 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	id->limit = id->last_meal + id->data->time_die;
	print_state(id, EAT);
	usleep(id->data->time_eat);
	id->nb_meals++;
	id->is_eating = 0;
	sem_post(id->philo_s);
	sem_post(id->must_eat_s);
}

static void		philo_sleep(t_id *id)
{
	print_state(id, SLEEP);
	sem_post(id->data->forks_s);
	sem_post(id->data->forks_s);
	usleep(id->data->time_sleep);
}

int				exec_philo(t_id *id)
{
	pthread_t	thread;

	id->last_meal = get_time();
	id->limit = id->last_meal + id->data->time_die;
	if (pthread_create(&thread, NULL, &monitor, id) != 0)
		return (1);
	pthread_detach(thread);
	while (1)
	{
		taking_forks(id);
		philo_eat(id);
		philo_sleep(id);
		print_state(id, THINK);
	}
	return (0);
}
