/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:36:07 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/18 23:45:07 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	checker(t_table *table, t_philo *philo)
{
	int	i;

	while (!(table->all_ate))
	{
		i = 0;
		while (i < table->chairs && !(table->death))
		{
			pthread_mutex_lock(&(table->check));
			if ((get_time() - philo[i].last_meal) > table->time_to_die)
			{
				print_action(table, i, "died");
				pthread_mutex_lock(&(table->print));
				table->death = 1;
				pthread_mutex_unlock(&(table->print));
			}
			pthread_mutex_unlock(&(table->check));
			i++;
		}
		if (table->death)
			break ;
		check_meals(table, philo);
	}
}

void	check_meals(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(table->check));
	if (table->meal_nb != -1)
	{
		while (i < table->chairs)
		{
			if (philo[i].meals < table->meal_nb)
				break ;
			i++;
		}
		if (i == table->chairs)
			table->all_ate = 1;
	}
	pthread_mutex_unlock(&(table->check));
}
