/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:44:50 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/18 23:28:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				meals;
	int				left;
	int				right;
	long long		last_meal;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				chairs;
	int				start;
	int				meal_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				death;
	int				all_ate;
	pthread_mutex_t	check;
	long long		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_table;

// philosophers.c
int			main(int argc, char **argv);
int			check_input(int argc, char **argv);
void		print_usage(void);

// ft_initialize.c
int			ft_initialize(t_table *table, char **argv, int argc);
void		init_mutex(t_table *table);
void		init_philo(t_table *table);

// ft_philosopher.c
void		ft_start(t_table *table);
void		ft_end(t_table *table);
void		*action(void *arg);
void		*action_death(void *arg);

// ft_phiosopher_actions.c
void		print_action(t_table *table, int id, char *str);
void		action_sleep(t_philo *philo, t_table *table);
void		action_think(t_philo *philo, t_table *table);
void		action_eat(t_philo *philo, t_table *table);
void		take_forks(t_philo *philo, t_table *table);

// ft_check.c
void		check_meals(t_table *table, t_philo *philo);
void		checker(t_table *table, t_philo *philo);

// ft_utilities.c
int			ft_atoi(const char *nptr);
char		*ft_strchr(const char *s, int c);
long long	get_time(void);

#endif