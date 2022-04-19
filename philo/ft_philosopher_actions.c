/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher_actions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:52:32 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/18 23:55:34 by jkarosas         ###   ########.fr       */
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
	pthread_mutex_lock(&(table->check));
	print_action(table, philo->id, "is eating");
	philo->last_meal = get_time();
	philo->meals += 1;
	pthread_mutex_unlock(&(table->check));
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&(table->forks[philo->left]));
	pthread_mutex_unlock(&(table->forks[philo->right]));
}

void	take_forks(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&(table->forks[philo->left]));
	print_action(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&(table->forks[philo->right]));
	print_action(table, philo->id, "has taken a fork");
}

void	print_action(t_table *table, int id, char *str)
{
	pthread_mutex_lock(&(table->print));
	if (!(table->death))
	{
		printf("%lli ", get_time() - table->start_time);
		printf("%i %s\n", id + 1, str);
	}
	pthread_mutex_unlock(&(table->print));
}
