/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:44:38 by galves-f          #+#    #+#             */
/*   Updated: 2024/10/17 16:06:30 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_table *t, t_philo *p)
{
	pthread_mutex_lock(&(t->forks[p->left_fork_id]));
	print(t, p, TAKEN_FORK);
	if (t->philo_nb == 1)
	{
		pthread_mutex_unlock(&(t->forks[p->left_fork_id]));
		smart_sleep(t->time_to_die * 2, t);
		return ;
	}
	pthread_mutex_lock(&(t->forks[p->right_fork_id]));
	print(t, p, TAKEN_FORK);
	pthread_mutex_lock(&(t->meals_check));
	print(t, p, EAT);
	p->last_meal = timestamp();
	pthread_mutex_unlock(&(t->meals_check));
	smart_sleep(t->time_to_eat, t);
	(p->meals)++;
	pthread_mutex_unlock(&(t->forks[p->left_fork_id]));
	pthread_mutex_unlock(&(t->forks[p->right_fork_id]));
}

void	*start_philo(void *philo_ptr)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)philo_ptr;
	t = p->table;
	if (p->id % 2)
		usleep(15000);
	while (!stop_check(t))
	{
		eat(t, p);
		pthread_mutex_lock(&(t->meals_check));
		if (t->all_ate || (t->max_meals > 0 && p->meals >= t->max_meals))
		{
			pthread_mutex_unlock(&(t->meals_check));
			break ;
		}
		pthread_mutex_unlock(&(t->meals_check));
		print(t, p, SLEEP);
		smart_sleep(t->time_to_sleep, t);
		print(t, p, THINK);
	}
	return (NULL);
}
