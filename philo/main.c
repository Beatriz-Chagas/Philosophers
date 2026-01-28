/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas <bchagas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 01:50:39 by bchagas           #+#    #+#             */
/*   Updated: 2026/01/28 06:09:36 by bchagas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_rules	rules;
	
	if (parse_args(ac, av, &rules))
	{
		printf("Invalid arguments.\n");
		return (1);
	}
	else 
	{
		printf("Philos: %s\n", av[1]); 
		printf("Time to die: %s\n", av[2]); 
		printf("Time to eat: %s\n", av[3]); 
		printf("Time to slep: %s\n", av[4]); 
		if (ac == 6) 
			printf("Number of times each philosopher must eat: %s\n", av[5]);
	}
	return (0);
}
