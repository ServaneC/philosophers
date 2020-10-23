/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:44:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/22 15:30:20 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		print_error(void)
{
	ft_putstr("Error: philo_one need 4 or 5 NUMERIC arguments \n");
	ft_putstr("-> number_of_philosopher time_to_die time_to_eat time");
	ft_putstr("_to_sleep [number_of_time_each_philosophers_must_eat]\n");
	return (0);
}

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
	else if (action == END)
		return ("each philosopher has eaten the required number of time\n");
	return ("died\n");
}

void	*print_state(t_id *id, int action)
{
	static int	end;

	if (!end)
	{
		sem_wait(id->data->wr_right);
		ft_putnbr(timestamp_ms(id->data->start));
		write(1, " ", 1);
		if (action != END)
		{
			ft_putnbr(id->philo_id);
			write(1, " ", 2);
		}
		if (action >= DEAD)
			end++;
		write(1, action_message(action), ft_strlen(action_message(action)));
		if (!end)
			sem_post(id->data->wr_right);
	}
	return (NULL);
}
