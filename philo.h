#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define DEBUG 1
# define MAX_PHILOSOPHERS 250
# define MAX_THINK_TIME 1000
# define MAX_SLEEP_TIME 1000
# define MAX_EAT_TIME 1000

typedef enum e_action
{
	EAT,
	THINK,
	SLEEP,
	DIED,
	TAKEN_FORK,
}					t_action;

struct s_table;

typedef struct s_philo
{
	int				id;
	int				right_fork_id;
	int				left_fork_id;
	int				meals;
	long long		last_meal;
	struct s_table	*table;
	pthread_t		thread_id;
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
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];
	pthread_mutex_t	print;
	pthread_mutex_t	meals_check;
}					t_table;

void				*safe_malloc(size_t size);
int					ft_atoi(const char *nptr);
int					check_args(int ac, char **av);
int					init(char **av, t_table *t);
int					start(t_table *t);
long long			timestamp(void);
void				print(t_table *t, t_philo *p, t_action action);
void				smart_sleep(long long time, t_table *t);

#endif
