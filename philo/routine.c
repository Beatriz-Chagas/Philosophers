/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas <bchagas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:06:13 by bchagas           #+#    #+#             */
/*   Updated: 2026/02/03 07:25:42 by bchagas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
	}
	else 
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
	}
	print_status(p, "has taken forks");
}

void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	eat_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->rules->death);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->rules->death);
	
	print_status(p, "is eating");
	ft_usleep(p->rules->time_eat);
	
	p->meals_eaten++;
	print_status(p, "is sleeping");
	ft_usleep(p->rules->time_sleep);
	
	print_status(p, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*p;
	
	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&p->rules->death);
		if (p->rules->dead || (p->rules->must_eat != 1 
			&& p->meals_eaten >= p->rules->must_eat))
		{
			pthread_mutex_unlock(&p->rules->death);
			break;
		}
		pthread_mutex_unlock(&p->rules->death);
		take_forks(p);
		eat_sleep(p);
		put_forks(p);    
	}
	return (NULL);
}
