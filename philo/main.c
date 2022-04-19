/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:48:39 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/13 09:30:39 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6 || check_input(argc, argv))
	{
		print_usage();
		return (1);
	}
	if (ft_initialize(&table, argv, argc))
		return (1);
	ft_start(&table);
	return (0);
}

int	check_input(int argc, char **argv)
{
	char	*c;
	int		i;
	int		j;

	i = 1;
	c = "-0123456789";
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(ft_strchr(c, argv[i][j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	print_usage(void)
{
	printf("Usage: ./philo [number_of_philosophers] ");
	printf("[time_to_die] [time_to_eat] [time_to_sleep]\n");
	printf("Optional: You can add the number of times ");
	printf("each philosopher must eat at the end\n");
}
