/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:25:45 by schene            #+#    #+#             */
/*   Updated: 2020/10/27 13:07:27 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern int		g_forks;
extern int		g_death;
extern sem_t	*g_sem;

static void		taking_forks(t_id *id)
{
	g_forks -= 2;
	sem_wait(g_sem);
	sem_wait(g_sem);
	print_state(id, TAKE_FORK);
	print_state(id, TAKE_FORK);
}

static t_u64	philo_eat(t_id *id)
{
	t_u64		start_meal;

	start_meal = get_time_ms();
	id->is_eating = 1;
	print_state(id, EAT);
	usleep(id->data->time_eat);
	g_forks += 2;
	sem_post(g_sem);
	sem_post(g_sem);
	id->is_eating = 0;
	return (start_meal);
}

void			*philo_life(void *arg)
{
	t_id	*id;
	int		nb_meals;

	id = (t_id *)arg;
	nb_meals = 0;
	id->last_meal = get_time_ms();
	while (timestamp_ms(id->last_meal) < id->data->time_die && !(g_death))
	{
		// printf("- %d->%d\n", id->philo_id, g_forks);
		if (g_forks >= 2)
		{
			taking_forks(id);
			// printf("= %d->%d\n", id->philo_id, g_forks);
			id->last_meal = philo_eat(id);
			if (++nb_meals == id->data->must_eat)
				return (NULL);
			print_state(id, SLEEP);
			usleep(id->data->time_sleep);
			print_state(id, THINK);
		}
	}
	return (print_state(id, DEAD));
}

int			exec_philo(t_id *id)
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
		// printf("= %d->%d\n", id->philo_id, g_forks);
		id->last_meal = philo_eat(id);
		if (++nb_meals == id->data->must_eat)
			return (0);
		print_state(id, THINK);
	}
	return (0);
}
