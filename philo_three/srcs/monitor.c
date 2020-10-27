/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:56:36 by schene            #+#    #+#             */
/*   Updated: 2020/10/27 13:45:25 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitor(void *arg)
{
	t_id		*id;

	id = (t_id *)arg;
	while (1)
	{
		if (!id->is_eating && timestamp_ms(id->last_meal) > id->data->time_die)
		{
			print_state(id, DEAD);
			sem_post(id->data->sem_death);
			return ((void*)0);
		}
		usleep(1000);
	}
	return ((void*)0);
}
