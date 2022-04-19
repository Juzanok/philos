/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 00:06:32 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/18 23:28:42 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_initialize(t_table *table, char **argv, int argc)
{
	table->chairs = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->start = 0;
	table->death = 0;
	table->all_ate = 0;
	table->meal_nb = -1;
	if (argc == 6)
	{
		table->meal_nb = ft_atoi(argv[5]);
		if (table->meal_nb <= 0)
			return (1);
	}
	if (table->chairs < 1 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (1);
	init_mutex(table);
	init_philo(table);
	return (0);
}

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->chairs);
	while (i < table->chairs)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(table->print), NULL);
	pthread_mutex_init(&(table->check), NULL);
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
		table->philo[i].left = i;
		if (i != table->chairs - 1)
			table->philo[i].right = i + 1;
		i++;
	}
	table->philo[table->chairs - 1].right = 0;
}
