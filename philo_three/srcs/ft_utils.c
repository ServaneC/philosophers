/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:59:36 by schene            #+#    #+#             */
/*   Updated: 2020/10/26 11:59:55 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	f;
	int n;

	i = 0;
	f = 0;
	n = 1;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
				str[i] == '\f' || str[i] == '\r' || str[i] == ' ') && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	if ((!(str[i] >= '0' && str[i] <= '9')) && str[i])
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		f = (f * 10 + (str[i] - 48));
		i++;
	}
	return (f * n);
}

int		is_all_digit(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}
