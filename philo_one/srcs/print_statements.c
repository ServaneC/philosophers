/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:44:37 by schene            #+#    #+#             */
/*   Updated: 2020/10/17 18:51:33 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_state(int timestamp, int id, int action)
{
	char	*tab[5];

	tab[0] = "has taken a fork";
	tab[1] = "is eating";
	tab[2] = "is sleeping";
	tab[3] = "is thinking";
	tab[4] = "died";
	printf("%d %d %s\n", timestamp, id, tab[action]);
}
