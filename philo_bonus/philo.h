/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:35:59 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/30 09:27:27 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define DEBUG 1
# define MAX_PHILOSOPHERS 250
# define MAX_THINK_TIME 1000
# define MAX_SLEEP_TIME 1000
# define MAX_EAT_TIME 1000

typedef enum e_action
{
	EAT,
	DONE_EAT,
	THINK,
	SLEEP,
	DIED,
	TAKEN_FORK,
}					t_action;

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal;
	struct s_table	*table;
	pthread_t		check_death;
	pid_t			pid;
}					t_philo;

typedef struct s_table
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				stop;
	int				all_ate;
	long long		first_timestamp;
	t_philo			philo[MAX_PHILOSOPHERS];
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meals_check;
}					t_table;

void				*safe_malloc(size_t size);
int					ft_atoi(const char *nptr);
int					check_args(int ac, char **av);
int					init(char **av, t_table *t);
int					start(t_table *t);
long long			timestamp(void);
void				print(t_table *t, t_philo *p, t_action action);
void				smart_sleep(long long time, t_table *t);
void				eat(t_table *t, t_philo *p);
void				*start_philo(void *philo_ptr);
void				*freddy_krueger(void *ptr_philo);

#endif
