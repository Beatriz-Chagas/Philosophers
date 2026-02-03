/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas <bchagas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:46:31 by bchagas           #+#    #+#             */
/*   Updated: 2026/02/03 07:23:01 by bchagas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start;
	
	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void	print_status(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->rules->print);
	if (!p->rules->dead)
		printf("%ld %d %s\n", get_time() - p->rules->start_time, p->id, msg);
	pthread_mutex_unlock(&p->rules->print);
}

