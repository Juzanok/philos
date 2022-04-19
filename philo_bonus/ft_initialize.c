/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 00:06:32 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/14 01:12:40 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_initialize(t_table *table, char **argv, int argc)
{
	table->chairs = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->death = 0;
	table->meal_nb = -1;
	if (argc == 6)
	{
		table->meal_nb = ft_atoi(argv[5]);
		if (table->meal_nb <= 0)
			return (1);
	}
	if (table->time_to_sleep < 0 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->chairs < 1)
		return (1);
	init_smphr(table);
	init_philo(table);
	return (0);
}

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->chairs);
	while (i < table->chairs)
	{
		table->philo[i].id = i;
		table->philo[i].meals = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].table = table;
		table->philo[i].smphr = ft_itoa(i);
		sem_unlink(table->philo[i].smphr);
		table->philo[i].check = sem_open(table->philo[i].smphr,
				O_CREAT, S_IRWXU, 1);
		i++;
	}
}

void	init_smphr(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("finished");
	sem_unlink("end");
	table->forks = sem_open("forks", O_CREAT, S_IRWXU, table->chairs);
	table->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	table->finished = sem_open("finished", O_CREAT, S_IRWXU, 0);
	table->end = sem_open("end", O_CREAT, S_IRWXU, 0);
}
