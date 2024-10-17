/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:29:05 by galves-f          #+#    #+#             */
/*   Updated: 2024/10/17 17:34:56 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_philo_meals(t_table *t, t_philo *p, t_meals_check check)
{
	int	meals;

	pthread_mutex_lock(&(t->meals_check));
	if (check == LAST_MEAL)
		meals = p->last_meal;
	else if (check == MEALS)
		meals = p->meals;
	else
		meals = t->all_ate;
	pthread_mutex_unlock(&(t->meals_check));
	return (meals);
}

void	set_philo_meals(t_table *t, t_philo *p, t_meals_check check, int value)
{
	pthread_mutex_lock(&(t->meals_check));
	if (check == LAST_MEAL)
		p->last_meal = value;
	else if (check == MEALS)
		p->meals = value;
	else
		t->all_ate = value;
	pthread_mutex_unlock(&(t->meals_check));
}

void	increment_philo_meals(t_table *t, t_philo *p)
{
	pthread_mutex_lock(&(t->meals_check));
	(p->meals)++;
	pthread_mutex_unlock(&(t->meals_check));
}
