/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:44:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/18 14:52:44 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char	*action_message(int action)
{
	if (action == TAKE_FORK)
		return ("has taken a fork\n");
	else if (action == EAT)
		return ("is eating\n");
	else if (action == SLEEP)
		return ("is sleeping\n");
	else if (action == THINK)
		return ("is thinking\n");
	return ("died\n");
}

void	print_state(t_id *id, int action)
{
	static int end;

	pthread_mutex_lock(&id->data->wr_right);
	if (!end)
	{
		ft_putnbr(timestamp_ms(id->philo->start));
		write(1, " ", 1);
		ft_putnbr(id->philo_id);
		if (action == DEAD)
			end = 1;
		write(1, "\t", 1);
		write(1, action_message(action), ft_strlen(action_message(action)));
	}
	pthread_mutex_unlock(&id->data->wr_right);
}
