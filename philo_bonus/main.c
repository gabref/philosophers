/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:31:32 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/28 11:54:13 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (check_args(ac, av) != 0)
		return (1);
	if (init(av, &table) != 0)
	{
		printf("Error initializing simulation\n");
		return (1);
	}
	if (start(&table) != 0)
	{
		printf("Error in simulation\n");
		return (1);
	}
	return (0);
}
