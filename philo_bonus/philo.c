/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:44:38 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/30 09:47:23 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_table *t, t_philo *p)
{
	sem_wait(t->forks);
	print(t, p, TAKEN_FORK);
	if (t->philo_nb == 1)
	{
		sem_wait(t->forks);
		smart_sleep(t->time_to_die * 2, t);
		return ;
	}
	sem_wait(t->forks);
	print(t, p, TAKEN_FORK);
	sem_wait(t->meals_check);
	print(t, p, EAT);
	p->last_meal = timestamp();
	sem_post(t->meals_check);
	smart_sleep(t->time_to_eat, t);
	(p->meals)++;
	sem_post(t->forks);
	sem_post(t->forks);
}

void	*start_philo(void *philo_ptr)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)philo_ptr;
	p->last_meal = timestamp();
	t = p->table;
	if (p->id % 2)
		usleep(15000);
	pthread_create(&(p->check_death), NULL, freddy_krueger, philo_ptr);
	while (!(t->stop))
	{
		eat(t, p);
		if (t->all_ate || (t->max_meals > 0 && p->meals >= t->max_meals))
			break ;
		print(t, p, SLEEP);
		smart_sleep(t->time_to_sleep, t);
		print(t, p, THINK);
	}
	pthread_join(p->check_death, NULL);
	if (t->stop)
		exit(1);
	exit(0);
}
