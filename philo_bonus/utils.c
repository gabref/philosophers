/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:51:30 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/30 09:00:34 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr && is_space(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		result = (result * 10) + (*nptr++ - 48);
	return (result * sign);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	smart_sleep(long long time, t_table *t)
{
	long long	current;

	current = timestamp();
	while (!(t->stop))
	{
		if (timestamp() - current >= time)
			break ;
		usleep(50);
	}
}

void	print(t_table *t, t_philo *p, t_action action)
{
	sem_wait(t->print);
	if (!(t->stop))
	{
		printf("%lli %d ", timestamp() - t->first_timestamp, p->id);
		if (action == TAKEN_FORK)
			printf("has taken a fork\n");
		else if (action == EAT)
			printf("is eating\n");
		else if (action == DONE_EAT)
			printf("done eating\n");
		else if (action == THINK)
			printf("is thinking\n");
		else if (action == SLEEP)
			printf("is sleeping\n");
		else
			printf("died\n");
	}
	sem_post(t->print);
}
