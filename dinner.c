#include "philo.h"
#include <pthread.h>

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
	while (!(t->stop))
	{
		eat(t, p);
		if (t->all_ate || (t->max_meals > 0 && p->meals >= t->max_meals))
			break ;
		print(t, p, SLEEP);
		smart_sleep(t->time_to_sleep, t);
		print(t, p, THINK);
	}
	return (NULL);
}

void	freddy_krueger(t_table *t)
{
	int	i;

	while (!(t->stop) && !(t->all_ate))
	{
		i = -1;
		while (++i < t->philo_nb && !(t->stop))
		{
			pthread_mutex_lock(&(t->meals_check));
			if (timestamp() - t->philo[i].last_meal > t->time_to_die
				&& t->philo[i].meals != t->max_meals)
			{
				print(t, &(t->philo[i]), DIED);
				t->stop = 1;
			}
			pthread_mutex_unlock(&(t->meals_check));
			usleep(100);
		}
		if (t->stop)
			break ;
		i = 0;
		while (t->max_meals != -1 && i < t->philo_nb
			&& t->philo[i].meals >= t->max_meals)
			i++;
		if (i == t->philo_nb)
			t->all_ate = 1;
	}
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
		t->philo[i].last_meal = timestamp();
	}
	freddy_krueger(t);
	end(t);
	return (0);
}
