/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:39:10 by galves-f          #+#    #+#             */
/*   Updated: 2024/10/17 17:52:47 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meals_check(t_table *t)
{
	int	i;

	if (t->max_meals == -1)
		return ;
	i = 0;
	while (i < t->philo_nb)
	{
		if (get_philo_meals(t, &t->philo[i], MEALS) < t->max_meals)
			return ;
		i++;
	}
	set_philo_meals(t, NULL, ALL_ATE, 1);
}

int	stop_check(t_table *t)
{
	pthread_mutex_lock(&(t->stop_check));
	if (t->stop)
	{
		pthread_mutex_unlock(&(t->stop_check));
		return (1);
	}
	pthread_mutex_unlock(&(t->stop_check));
	return (0);
}

void	*freddy_krueger(t_table *t)
{
	int	i;
	int	diff;

	while (!stop_check(t) && !get_philo_meals(t, NULL, ALL_ATE))
	{
		i = -1;
		while (++i < t->philo_nb && !stop_check(t))
		{
			diff = timestamp() - get_philo_meals(t, &t->philo[i], LAST_MEAL);
			if (diff > t->time_to_die && get_philo_meals(t, &t->philo[i],
					MEALS) != t->max_meals)
			{
				print(t, &(t->philo[i]), DIED);
				pthread_mutex_lock(&(t->stop_check));
				t->stop = 1;
				pthread_mutex_unlock(&(t->stop_check));
			}
			usleep(100);
		}
		if (stop_check(t))
			break ;
		meals_check(t);
	}
	return (NULL);
}

void	end(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_nb)
		pthread_join(t->philo[i++].thread_id, NULL);
	i = 0;
	while (i < t->philo_nb)
		pthread_mutex_destroy(&(t->forks[i++]));
	pthread_mutex_destroy(&(t->print));
	pthread_mutex_destroy(&(t->meals_check));
}

int	start(t_table *t)
{
	int	i;

	t->first_timestamp = timestamp();
	i = -1;
	while (++i < t->philo_nb)
	{
		pthread_create(&(t->philo[i].thread_id), NULL, &start_philo,
			&(t->philo[i]));
		set_philo_meals(t, &(t->philo[i]), LAST_MEAL, timestamp());
	}
	freddy_krueger(t);
	end(t);
	return (0);
}
