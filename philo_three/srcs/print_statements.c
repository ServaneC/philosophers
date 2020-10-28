/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 14:32:34 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		return (" has taken a fork\n");
	else if (action == EAT)
		return (" is eating\n");
	else if (action == SLEEP)
		return (" is sleeping\n");
	else if (action == THINK)
		return (" is thinking\n");
	else if (action == END)
		return ("each philosopher has eaten the required number of time\n");
	return (" died\n");
}

void	print_state(t_id *id, int action)
{
	sem_wait(id->data->wr_right);
	sem_wait(id->data->wr_dead);
	ft_putnbr(timestamp_ms(id->data->start));
	write(1, " ", 1);
	if (action != END)
		ft_putnbr(id->philo_id + 1);
	write(1, action_message(action), ft_strlen(action_message(action)));
	if (action < DEAD)
		sem_post(id->data->wr_dead);
	sem_post(id->data->wr_right);
}
