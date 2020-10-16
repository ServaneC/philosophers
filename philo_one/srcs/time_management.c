/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:28:03 by schene            #+#    #+#             */
/*   Updated: 2020/10/16 11:48:14 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			timestamp_ms(t_u64 start_time)
{
	t_u64			current_time;
	struct timeval	tv;
	int				diff;

	gettimeofday(&tv, NULL);
	current_time = (1000000 * tv.tv_sec) + tv.tv_usec;
	diff = (current_time - start_time) / 1000;
	return (diff);
}

t_u64		get_time_ms(void)
{
	t_u64			current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = (1000000 * tv.tv_sec) + tv.tv_usec;
	return (current_time);
}
