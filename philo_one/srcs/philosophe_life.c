/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:13:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/16 13:10:36 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		taking_forks(t_idphilo *idphilo)
{
	g_forks[0] = 1;
	g_forks[1] = 1;
	pthread_mutex_lock(&g_mutex[0]);
	printf("%d %d has taken a fork\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	pthread_mutex_lock(&g_mutex[1]);
	printf("%d %d has taken a fork\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
}

static void		philo_eat(t_idphilo *idphilo)
{
	printf("%d %d is eating\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	usleep(idphilo->philo->time_eat);
	g_forks[0] = 0;
	g_forks[1] = 0;
	pthread_mutex_unlock(&g_mutex[0]);
	pthread_mutex_unlock(&g_mutex[1]);
}

static void		philo_sleep(t_idphilo *idphilo)
{
	printf("%d %d is sleeping\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	usleep(idphilo->philo->time_sleep);
}

void			*philosophe_life(void *arg)
{
	t_idphilo	*idphilo;
	t_u64		last_meal;
	int			time_passed;

	idphilo = (t_idphilo *)arg;
	last_meal = get_time_ms();
	time_passed = 0;
	while (time_passed <= idphilo->philo->time_die)
	{
		if (g_forks[0] == 0 && g_forks[1] == 0)
		{
			taking_forks(idphilo);
			last_meal = get_time_ms();
			philo_eat(idphilo);
			if (timestamp_ms(last_meal) <= idphilo->philo->time_die)
				philo_sleep(idphilo);
			if (timestamp_ms(last_meal) <= idphilo->philo->time_die)
				printf("%d %d is thinking\n", timestamp_ms(
					idphilo->philo->start_time), idphilo->philo_id);
		}
		time_passed = timestamp_ms(last_meal);
	}
	printf("%d %d died\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	return (NULL);
}
