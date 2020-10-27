/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:56:36 by schene            #+#    #+#             */
/*   Updated: 2020/10/27 13:20:05 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

// void	*monitor_count(void *state_v)
// {
// 	t_state *state;
// 	int		total;
// 	int		i;

// 	state = (t_state*)state_v;
// 	total = 0;
// 	while (total < state->must_eat_count)
// 	{
// 		i = 0;
// 		while (i < state->amount)
// 			sem_wait(state->philos[i++].eat_count_m);
// 		total++;
// 	}
// 	display_message(&state->philos[0], TYPE_OVER);
// 	sem_post(state->somebody_dead_m);
// 	return ((void*)0);
// }

void	*monitor(void *arg)
{
	t_id		*id;

	id = (t_id *)arg;
	while (1)
	{
		// sem_wait(philo->mutex);
		if (!id->is_eating && timestamp_ms(id->last_meal) > id->data->time_die)
		{
			print_state(id, DEAD);
			// sem_post(philo->mutex);
			sem_post(id->data->sem_death);
			return ((void*)0);
		}
		// sem_post(philo->mutex);
		usleep(1000);
	}
	return ((void*)0);
}

// int	start_monitor_thread(t_state *state)
// {
// 	pthread_t	tid;

// 	if (state->must_eat_count > 0)
// 	{
// 		if (pthread_create(&tid, NULL, &monitor_count, (void*)state) != 0)
// 			return (1);
// 		pthread_detach(tid);
// 	}
// 	return (0);
// }