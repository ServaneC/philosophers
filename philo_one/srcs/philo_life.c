/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:13:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/17 16:34:56 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		taking_forks(t_idphilo *idphilo)
{
	idphilo->data->forks[idphilo->right_frk] = 1;
	idphilo->data->forks[idphilo->left_frk] = 1;
	pthread_mutex_lock(&idphilo->data->mutex[idphilo->right_frk]);
	printf("%d %d has taken a fork\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	pthread_mutex_lock(&idphilo->data->mutex[idphilo->left_frk]);
	printf("%d %d has taken a fork\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
}

static t_u64	philo_eat(t_idphilo *idphilo)
{
	t_u64		start_meal;

	start_meal = get_time_ms();
	printf("%d %d is eating\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	usleep(idphilo->philo->time_eat);
	idphilo->data->forks[idphilo->right_frk] = 0;
	idphilo->data->forks[idphilo->left_frk] = 0;
	pthread_mutex_unlock(&idphilo->data->mutex[idphilo->right_frk]);
	pthread_mutex_unlock(&idphilo->data->mutex[idphilo->left_frk]);
	return (start_meal);
}

static void		philo_sleep(t_idphilo *idphilo)
{
	printf("%d %d is sleeping\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	usleep(idphilo->philo->time_sleep);
}

void			*philo_life(void *arg)
{
	t_idphilo	*idphilo;
	t_u64		last_meal;
	int			time_passed;

	idphilo = (t_idphilo *)arg;
	last_meal = get_time_ms();
	time_passed = 0;
	while (time_passed <= idphilo->philo->time_die && !(g_death))
	{
		if (idphilo->data->forks[idphilo->right_frk] == 0 &&
			idphilo->data->forks[idphilo->left_frk] == 0)
		{
			taking_forks(idphilo);
			last_meal = philo_eat(idphilo);
			philo_sleep(idphilo);
			printf("%d %d is thinking\n", timestamp_ms(
				idphilo->philo->start_time), idphilo->philo_id);
		}
		time_passed = timestamp_ms(last_meal);
	}
	if (!g_death)
		printf("%d %d died\n",
			timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	g_death++;
	return (NULL);
}
