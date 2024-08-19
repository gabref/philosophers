#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 100
# define MAX_THINK_TIME 1000
# define MAX_SLEEP_TIME 1000
# define MAX_EAT_TIME 1000

typedef struct s_philo
{
	int	id;
}		t_philo;

void	*safe_malloc(size_t size);

#endif
