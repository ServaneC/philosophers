/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:47:14 by schene            #+#    #+#             */
/*   Updated: 2020/10/13 12:32:37 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main()
{
	struct timeval start_time;
	struct timeval end_time;

	gettimeofday(&start_time, NULL);
	usleep(1);	
	gettimeofday(&end_time, NULL);
	printf("seconds : %ld,%ld\n\n",
    start_time.tv_sec, start_time.tv_usec);
	printf("seconds : %ld,%ld\n",
    end_time.tv_sec, end_time.tv_usec);
	return (0);
}