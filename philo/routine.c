/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chagas <chagas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:06:13 by bchagas           #+#    #+#             */
/*   Updated: 2026/05/26 15:10:19 by chagas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	take_forks(t_philo *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (simulation_finished(p->rules))
		return ;
	first = p->left_fork;
	second = p->right_fork;
	if (first == second)
	{
		pthread_mutex_lock(first);
		print_status(p, "has taken a fork");
		ft_usleep(p->rules->time_die, p->rules);
		pthread_mutex_unlock(first);
		return ;
	}
	if (first > second)
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(first);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(second);
	print_status(p, "has taken a fork");
}

void	eat_sleep(t_philo *p)
{
	print_status(p, "is eating");
	pthread_mutex_lock(&p->rules->death);
	p->last_meal = get_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->rules->death);
	ft_usleep(p->rules->time_eat, p->rules);
	put_forks(p);
	print_status(p, "is sleeping");
	ft_usleep(p->rules->time_sleep, p->rules);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (!simulation_finished(p->rules))
	{
		take_forks(p);
		if (simulation_finished(p->rules))
			break ;
		eat_sleep(p);
		if (simulation_finished(p->rules))
			break ;
		print_status(p, "is thinking");
		usleep(500);
	}
	return (NULL);
}
