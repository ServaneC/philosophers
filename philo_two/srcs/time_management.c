/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:28:03 by schene            #+#    #+#             */
/*   Updated: 2020/10/20 10:39:22 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			timestamp_ms(t_u64 start)
{
	t_u64			current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = (1000000 * tv.tv_sec) + tv.tv_usec;
	return ((current_time - start) / 1000);
}

t_u64		get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((1000000 * tv.tv_sec) + tv.tv_usec);
}
