/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:28:21 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 15:08:33 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			timestamp_ms(t_u64 start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((1000000 * tv.tv_sec) + tv.tv_usec) - start) / 1000);
}

t_u64		get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((1000000 * tv.tv_sec) + tv.tv_usec);
}

t_u64		get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (t_u64)1000) + (tv.tv_usec / 1000));
}
