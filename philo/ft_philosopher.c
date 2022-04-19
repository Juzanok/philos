/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:52:32 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/18 23:42:55 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_start(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = table->philo;
	table->start_time = get_time();
	if (table->chairs == 1)
	{
		pthread_create(&(philo[0].thread), NULL, action_death, &(philo[0]));
		ft_end(table);
		return ;
	}
	while (i < table->chairs)
	{
		philo[i].last_meal = table->start_time;
		pthread_create(&(philo[i].thread), NULL, action, &(philo[i]));
		i++;
	}
	checker(table, philo);
	ft_end(table);
}

void	*action_death(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(&(table->forks[philo->left]));
	print_action(table, philo->id, "has taken a fork");
	usleep(table->time_to_die * 1000);
	print_action(table, philo->id, "died");
	pthread_mutex_unlock(&(table->forks[philo->left]));
	return (NULL);
}

void	*action(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
		usleep(table->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(&(table->check));
		if (table->death || table->all_ate)
		{
			pthread_mutex_unlock(&(table->check));
			break ;
		}
		pthread_mutex_unlock(&(table->check));
		action_eat(philo, table);
		action_sleep(philo, table);
		action_think(philo, table);
	}
	return (NULL);
}

void	ft_end(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->chairs)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->chairs)
	{
		pthread_mutex_destroy(&(table->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(table->print));
	pthread_mutex_destroy(&(table->check));
	free(table->forks);
	free(table->philo);
}
