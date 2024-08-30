/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:52:22 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/30 09:34:58 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
				"time_to_sleep [number_of_times_each_philosopher_must_eat]",
				av[0]);
		return (1);
	}
	return (0);
}

int	init_philos(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_nb)
	{
		t->philo[i].id = i;
		t->philo[i].meals = 0;
		t->philo[i].last_meal = 0;
		t->philo[i].table = t;
		i++;
	}
	return (0);
}

int	init_semaphores(t_table *t)
{
	sem_unlink("/philo_print");
	sem_unlink("/philo_fork");
	sem_unlink("/philo_meals_check");
	t->print = sem_open("/philo_print", O_CREAT, S_IRWXU, 1);
	t->forks = sem_open("/philo_fork", O_CREAT, S_IRWXU, t->philo_nb);
	t->meals_check = sem_open("/philo_meals_check", O_CREAT, S_IRWXU, 1);
	if (t->meals_check == SEM_FAILED || t->print == SEM_FAILED
		|| t->forks == SEM_FAILED)
		return (-1);
	return (0);
}

int	init(char **av, t_table *t)
{
	t->philo_nb = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	t->max_meals = -1;
	t->stop = 0;
	t->all_ate = 0;
	if (t->philo_nb < 1 || t->time_to_die < 0 || t->time_to_eat < 0
		|| t->time_to_sleep < 0 || t->philo_nb > MAX_PHILOSOPHERS)
	{
		printf("Invalid argument\n");
		return (-1);
	}
	if (av[5])
	{
		t->max_meals = ft_atoi(av[5]);
		if (t->max_meals < 1)
			return (-1);
	}
	if (init_semaphores(t) != 0)
		return (-1);
	if (init_philos(t) != 0)
		return (-1);
	return (0);
}
