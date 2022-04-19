/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:44:50 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/14 13:00:02 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				meals;
	long long		last_meal;
	pthread_t		thread;
	struct s_table	*table;
	char			*smphr;
	sem_t			*check;
}	t_philo;

typedef struct s_table
{
	int				chairs;
	int				meal_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				death;
	long long		start_time;
	sem_t			*forks;
	sem_t			*check;
	sem_t			*print;
	sem_t			*end;
	sem_t			*finished;
	t_philo			*philo;
}	t_table;

// main.c
int			main(int argc, char **argv);
void		print_usage(void);
int			check_input(int argc, char **argv);

// ft_initialize.c
int			ft_initialize(t_table *table, char **argv, int argc);
void		init_philo(t_table *table);
void		init_smphr(t_table *table);

// philo_actions.c
void		print_action(t_table *table, int id, char *str);
void		action_sleep(t_philo *philo, t_table *table);
void		action_think(t_philo *philo, t_table *table);
void		action_eat(t_philo *philo, t_table *table);
void		take_forks(t_philo *philo, t_table *table);

// philosophers.c
void		action(void *philo_void);
void		ft_start(t_table *table);
void		ft_end(t_table *table);
void		*checker(void *arg);
void		*ft_finished(void *arg);

// ft_utilities.c
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
long long	get_time(void);
size_t		ft_length(int n);

#endif