/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:58:33 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/27 12:47:15 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_switch
{
	size_t			n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_times;
	size_t			died;
	pthread_mutex_t	check;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
}	t_switch;

typedef struct s_philo
{
	size_t			id;
	size_t			start;
	size_t			last_meal;
	size_t			n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_times;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_switch	*context;
}	t_philo;

int		ft_check_args(t_switch *context, int ac, char **av);
int		ft_set_data(t_switch *context, int ac, char **av);
void	ft_init_data(t_switch *context);
int		ft_sleeping(t_philo *philo);
int		ft_thinking(t_philo *philo);
int		ft_eating(t_philo *philo);
size_t	ft_strlen(const char *s);
int		is_dead(t_philo *philo);
size_t	ft_atol(const char *s);
void	*routine(void *arg);
int		error_args(int ac);
size_t	ft_get_time(void);

#endif