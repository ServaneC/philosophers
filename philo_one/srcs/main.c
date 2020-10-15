/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/15 14:51:28 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		*philosophe_life(void *arg)
{
	t_philo		*philo;
	static int	id;
	int			i;

	philo = (t_philo *)arg;
	i = -1;
	id++;
	while (++i < 5)
	{
		if (forks[0] == 0 && forks[1] == 0)
		{
			pthread_mutex_lock(&mutex_forks[0]);
			printf("%d has taken a fork\n", id);
			forks[0] = 1;
			pthread_mutex_lock(&mutex_forks[1]);
			printf("%d has taken a fork\n", id);	
			forks[1] = 1;
			printf("%d is eating\n", id);
			usleep(philo->time_eat);
			pthread_mutex_unlock(&mutex_forks[0]);
			forks[0] = 0;
			pthread_mutex_unlock(&mutex_forks[1]);
			forks[1] = 0;
			printf("%d is sleeping\n", id);
			usleep(philo->time_sleep);
		}
		printf("%d is thinking\n", id);
	}
	return (NULL);
}

int			main(int ac, char **av)
{
	t_philo		*philo;
	int			i;

	i = -1;
	if ((philo = init_philo(ac, av)) == NULL)
		return (0);
	while (++i < 2)
	{
		pthread_mutex_init(&mutex_forks[i], NULL);
		if (pthread_create(&philosophers[i], NULL, philosophe_life, (void *)philo))
			return (-1);
	}
	i = -1;
	while (++i < 2)
	{
		if (pthread_join(philosophers[i], NULL))
			return (-1);
	}
	i = -1;
	while (++i < 2)
	{
		pthread_mutex_unlock(&mutex_forks[i]);
		pthread_mutex_destroy(&mutex_forks[i]);
	}
	free(philo);
	return (0);
}
