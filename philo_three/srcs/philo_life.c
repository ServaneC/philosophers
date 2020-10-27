/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:25:45 by schene            #+#    #+#             */
/*   Updated: 2020/10/27 13:48:42 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		taking_forks(t_id *id)
{
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
	sem_post(id->data->sem);
	sem_post(id->data->sem);
	return (start_meal);
}

int				exec_philo(t_id *id)
{
	int		nb_meals;

	nb_meals = 0;
	id->last_meal = get_time_ms();
	id->limit = timestamp_ms(id->last_meal) + id->data->time_die;
	if (pthread_create(&id->thread, NULL, &monitor, id) != 0)
		return (1);
	pthread_detach(id->thread);
	while (1)
	{
		taking_forks(id);
		id->is_eating = 1;
		id->last_meal = philo_eat(id);
		if (++nb_meals == id->data->must_eat)
			return (0);
		id->is_eating = 0;
		print_state(id, THINK);
	}
	return (0);
}
