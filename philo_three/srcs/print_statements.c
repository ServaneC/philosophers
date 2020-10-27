/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/10/26 15:57:07 by schene           ###   ########.fr       */
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

void	*print_state(t_data *data, int philo_id, int action)
{
	static int	end;

	if (action == DEAD)
		g_death++;
	sem_wait(data->wr_right);
	if (!end)
	{
		if (action >= DEAD)
			end++;
		ft_putnbr(timestamp_ms(data->start));
		write(1, " ", 1);
		if (action != END)
			ft_putnbr(philo_id + 1);
		write(1, action_message(action), ft_strlen(action_message(action)));
		if (action >= DEAD)
			exit(0);
	}
	sem_post(data->wr_right);
	return (NULL);
}
