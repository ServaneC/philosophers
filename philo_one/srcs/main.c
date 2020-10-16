/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/16 11:47:44 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		taking_forks(t_idphilo *idphilo)
{
	pthread_mutex_lock(&g_mutex[0]);
	printf("%d %d has taken a fork\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	g_forks[0] = 1;
	pthread_mutex_lock(&g_mutex[1]);
	printf("%d %d has taken a fork\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	g_forks[1] = 1;
}

void		philo_eat(t_idphilo *idphilo)
{
	printf("%d %d is eating\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	usleep(idphilo->philo->time_eat);
	pthread_mutex_unlock(&g_mutex[0]);
	g_forks[0] = 0;
	pthread_mutex_unlock(&g_mutex[1]);
	g_forks[1] = 0;
}

void		philo_sleep(t_idphilo *idphilo)
{
	printf("%d %d is sleeping\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	usleep(idphilo->philo->time_sleep);
}

void		*philosophe_life(void *arg)
{
	t_idphilo	*idphilo;
	t_u64		last_meal;
	int			time_passed;

	idphilo = (t_idphilo *)arg;
	last_meal = get_time_ms();
	time_passed = 0;
	while (time_passed <= idphilo->philo->time_die)
	{
		time_passed = timestamp_ms(last_meal);
		if (g_forks[0] == 0 && g_forks[1] == 0)
		{
			taking_forks(idphilo);
			last_meal = get_time_ms();
			philo_eat(idphilo);
			time_passed = timestamp_ms(last_meal);
			philo_sleep(idphilo);
		}
		time_passed = timestamp_ms(last_meal);
		printf("%d %d is thinking\n",
			timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	}
	printf("%d %d died\n",
		timestamp_ms(idphilo->philo->start_time), idphilo->philo_id);
	return (NULL);
}

int			main(int ac, char **av)
{
	t_philo		*philo;
	t_idphilo	*id[2];
	int			i;

	i = -1;
	if ((philo = init_philo(ac, av)) == NULL)
		return (0);
	while (++i < 2)
	{
		id[i] = init_idphilo(philo, i + 1);
		pthread_mutex_init(&g_mutex[i], NULL);
		if (pthread_create(&g_thread[i], NULL, philosophe_life, (void *)id[i]))
			return (-1);
	}
	i = -1;
	while (++i < 2)
	{
		if (pthread_join(g_thread[i], NULL))
			return (-1);
		pthread_mutex_unlock(&g_mutex[i]);
		pthread_mutex_destroy(&g_mutex[i]);
		free(id[i]);
	}
	free(philo);
	return (0);
}
