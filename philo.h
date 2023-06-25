/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:58:33 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/25 10:58:00 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	struct timeval	time;
	pthread_t		thread;
	size_t			last_meal;
	size_t			id;
}	t_philo;

typedef struct s_switch
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_times;
	int				death;
	int				id;
	pthread_t		*thread;
	t_philo			*philo;
	pthread_mutex_t	eating;
	pthread_mutex_t	sleeping;
	pthread_mutex_t	died;
}	t_switch;

void	*routine(void *arg);
int		is_dead(t_switch *context);
int		ft_sleeping(t_switch *context);
int		ft_eating(t_switch *context);
size_t	ft_strlen(const char *s);
long	ft_atol(const char *s);
int		error_args(int ac);
int		ft_check_args(t_switch *context, int ac, char **av);
size_t	ft_time_ms(struct timeval *time);

#endif
