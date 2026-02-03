/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas <bchagas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:53:09 by bchagas           #+#    #+#             */
/*   Updated: 2026/02/03 07:13:24 by bchagas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*p;
	int	i;
	long	now;

	p = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while(i < p[0].rules->philos)
		{
			pthread_mutex_lock(&p[0].rules->death);
			now = get_time();
			if (!p[0].rules->dead 
				&& now - p[i].last_meal > p[i].rules->time_die)
			{
				p[0].rules->dead = 1;
				print_status(&p[1], "died");
				pthread_mutex_unlock(&p[0].rules->death);
				return (NULL);   
			}
			pthread_mutex_unlock(&p[0].rules->death);
			i++;
		}
		usleep(1000);
	}
}
