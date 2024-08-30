/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:39:10 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/30 09:49:04 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_philo *p)
{
	if (p->table->max_meals != -1 && p->meals >= p->table->max_meals)
		return (1);
	return (0);
}

void	*freddy_krueger(void *ptr_philo)
{
	t_table	*t;
	t_philo	*p;

	p = (t_philo *)ptr_philo;
	t = p->table;
	while (!(t->stop))
	{
		sem_wait(t->meals_check);
		if (timestamp() - p->last_meal > t->time_to_die
			&& p->meals != t->max_meals)
		{
			print(t, p, DIED);
			t->stop = 1;
		}
		sem_post(t->meals_check);
		if (t->stop)
			break ;
		usleep(100);
		if (check_stop(p))
			break ;
	}
	return (NULL);
}

void	end(t_table *t)
{
	int	i;
	int	ret;

	waitpid(-1, &ret, 0);
	if (ret != 0)
	{
		i = -1;
		while (++i < t->philo_nb)
			kill(t->philo[i].pid, 15);
	}
	sem_unlink("/philo_print");
	sem_unlink("/philo_fork");
	sem_unlink("/philo_meals_check");
	sem_close(t->print);
	sem_close(t->forks);
	sem_close(t->meals_check);
}

int	start(t_table *t)
{
	int	i;

	t->first_timestamp = timestamp();
	i = -1;
	while (++i < t->philo_nb)
	{
		t->philo[i].pid = fork();
		if (t->philo[i].pid < 0)
			return (-1);
		if (t->philo[i].pid == 0)
			start_philo(&(t->philo[i]));
		usleep(100);
	}
	end(t);
	return (0);
}
