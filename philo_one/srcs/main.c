/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/15 11:53:49 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// int			time_convert(struct timeval	*start_time)
// {
// 	struct timeval	*current_time;
// 	int				time_ms;

// 	if (!(current_time = malloc(sizeof(current_time))))
// 		return (0);
// 	gettimeofday(current_time, NULL);
// 	time_ms = 0;
// 	time_ms = (current_time->tv_sec - start_time->tv_sec) * 1000;
// 	time_ms += (current_time->tv_usec / 1000);
// 	free(current_time);
// 	return (time_ms);
// }

// void		*thread_fct(void *arg)
// {
// 	t_philo		*philo;
// 	int			time;

// 	philo = (t_philo *)arg;
// 	time = time_convert(philo->start_time);
// 	printf("%d we are in a thread\n", time);
// 	return (NULL);
// }

void		*philosophe_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (forks[0] == 0 && forks[1] == 0)
		{
			pthread_mutex_lock(&mutex_forks[0]);
			printf("%d took a fork\n", philo->philo_id);
			pthread_mutex_lock(&mutex_forks[1]);
			printf("%d took a fork\n", philo->philo_id);
			forks[0] = 1;
			forks[1] = 1;
			printf("%d is eating\n", philo->philo_id);
			usleep(philo->time_eat);
			pthread_mutex_unlock(&mutex_forks[0]);
			pthread_mutex_unlock(&mutex_forks[1]);
			forks[0] = 0;
			forks[1] = 0;
			printf("%d is sleeping\n", philo->philo_id);
			usleep(philo->time_sleep);		
		}
		printf("%d is thinking\n", philo->philo_id);
	}
}

int			main(int ac, char **av)
{
	t_philo		*philo;
	// pthread_t	thread_id;
	int			i;

	i = -1;
	if ((philo = init_philo(ac, av)) == NULL)
		return (0);
	while (++i < 2)
	{
		pthread_mutex_init(&mutex_forks[i], NULL);
		philo->philo_id = i;
		pthread_create(&philosophers[i], NULL, philosophe_life, (void *)philo);
		pthread_join(philosophers[i], NULL);
	}
	// pthread_create(&thread_id, NULL, thread_fct, (void *)philo);
	// pthread_join(thread_id, NULL);
	free(philo);
	return (0);
}
