#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_INT 2147483647
#define MAX_LONG 

typedef struct s_rules
{
	int				philos;
	int				must_eat;
	int				dead;
	long			time_eat;	
	long			time_die;
	long			time_sleep;
	long			start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	pthread_mutex_t death;
} t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_rules         *rules;
}   t_philo;

int parse_args (int ac, char **av, t_rules *rules);
int init_forks(t_rules *r);
int	init_philos(t_rules *r, t_philo **philos);
void    *philo_routine(void *arg);
long	get_time(void);
void	ft_usleep(long time);
void    *monitor(void *arg);
void	print_status(t_philo *p, char *msg);

#endif