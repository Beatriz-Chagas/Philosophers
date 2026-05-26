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
	int					philos;
	int					must_eat;
	int					dead;
	long				time_eat;	
	long				time_die;
	long				time_sleep;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		death;
} t_rules;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					has_left;
	int					has_right;
	long				last_meal;
	int					meals_eaten;

	t_rules			*rules;

}	t_philo;

int		init_forks(t_rules *r);
int		simulation_finished(t_rules *rules);
int		parse_args (int ac, char **av, t_rules *rules);
long	get_time(void);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	ft_usleep(long ms, t_rules *r);
void	print_status(t_philo *p, char *msg);
#endif