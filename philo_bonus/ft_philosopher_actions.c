/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher_actions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:52:32 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/19 00:49:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action_sleep(t_philo *philo, t_table *table)
{
	print_action(table, philo->id, "is sleeping");
	usleep(table->time_to_sleep * 1000);
}

void	action_think(t_philo *philo, t_table *table)
{
	print_action(table, philo->id, "is thinking");
}

void	action_eat(t_philo *philo, t_table *table)
{
	take_forks(philo, table);
	sem_wait(philo->check);
	print_action(table, philo->id, "is eating");
	philo->last_meal = get_time();
	philo->meals += 1;
	sem_post(philo->check);
	usleep(table->time_to_eat * 1000);
	sem_post(table->forks);
	sem_post(table->forks);
}

void	take_forks(t_philo *philo, t_table *table)
{
	sem_wait(table->forks);
	print_action(table, philo->id, "has taken a fork");
	sem_wait(table->forks);
	print_action(table, philo->id, "has taken a fork");
}

void	print_action(t_table *table, int id, char *str)
{
	sem_wait(table->print);
	if (!table->death)
	{
		printf("%lli ", get_time() - table->start_time);
		printf("%i %s\n", id + 1, str);
	}
	sem_post(table->print);
}
