/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:44:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/28 19:04:20 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		print_error(char *message1, int nb, char *message2)
{
	ft_putstr("Error: ");
	if (message1)
		ft_putstr(message1);
	if (nb != -1)
		ft_putnbr(nb);
	if (message2)
		ft_putstr(message2);
	ft_putstr("\n");
	ft_putstr("Usage: number_of_philosopher time_to_die time_to_eat time");
	ft_putstr("_to_sleep [number_of_time_each_philosophers_must_eat]\n");
	return (1);
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
	static int		end;

	sem_wait(id->data->wr_right);
	if (!end)
	{
		ft_putnbr(timestamp_ms(id->data->start));
		write(1, " ", 1);
		if (action != END)
			ft_putnbr(id->philo_id + 1);
		if (action >= DEAD)
			end++;
		write(1, action_message(action), ft_strlen(action_message(action)));
	}
	sem_post(id->data->wr_right);
}
