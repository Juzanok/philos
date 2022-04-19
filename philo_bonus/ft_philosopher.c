/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:48:39 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/19 01:01:39 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_start(t_table *table)
{
	t_philo		*philo;
	pthread_t	thread;
	int			i;

	i = 0;
	philo = table->philo;
	table->start_time = get_time();
	while (i < table->chairs)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			action(&philo[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	if (table->meal_nb != -1)
		pthread_create(&thread, NULL, ft_finished, table);
	ft_end(table);
}

void	action(void *philo_void)
{
	t_table	*table;
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	table = philo->table;
	philo->last_meal = table->start_time;
	pthread_create(&philo->thread, NULL, checker, philo_void);
	if (philo->id % 2)
		usleep(table->time_to_eat * 1000);
	while (1)
	{
		action_eat(philo, table);
		sem_wait(philo->check);
		if (philo->meals >= table->meal_nb && table->meal_nb != -1)
			sem_post(table->finished);
		sem_post(philo->check);
		action_sleep(philo, table);
		action_think(philo, table);
	}
	exit(0);
}

void	*checker(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		sem_wait(philo->check);
		if ((get_time() - philo->last_meal) > table->time_to_die)
		{
			print_action(table, philo->id, "died");
			sem_wait(table->print);
			table->death = 1;
			sem_post(table->print);
			sem_wait(table->print);
			sem_post(table->end);
		}
		sem_post(philo->check);
		usleep(100);
	}
	return (NULL);
}

void	ft_end(t_table *table)
{
	int		i;

	sem_wait(table->end);
	i = -1;
	while (++i < table->chairs)
	{
		kill(table->philo[i].pid, SIGTERM);
		sem_close(table->philo[i].check);
		sem_unlink(table->philo[i].smphr);
		free(table->philo[i].smphr);
	}
	sem_close(table->end);
	sem_close(table->forks);
	sem_close(table->print);
	sem_close(table->finished);
	sem_unlink("end");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("finished");
	free(table->philo);
}

void	*ft_finished(void *arg)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)arg;
	while (i < table->chairs)
	{
		sem_wait(table->finished);
		i++;
	}
	sem_post(table->end);
	return (NULL);
}
