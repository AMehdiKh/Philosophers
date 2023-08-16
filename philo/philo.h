/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:58:33 by ael-khel          #+#    #+#             */
/*   Updated: 2023/08/16 06:34:21 by ael-khel         ###   ########.fr       */
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

typedef struct s_info
{
	size_t			n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_times;
	size_t			death;
	size_t			total_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
}	t_info;

typedef struct s_philo
{
	size_t			id;
	size_t			life;
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
	struct s_info	*context;
}	t_philo;

int		ft_check_args(t_info *context, int ac, char **av);
int		ft_usleep(t_philo *philo, size_t last_action,
			size_t current_action, int eating);
int		ft_dead_philo(t_info *context, size_t i);
int		ft_eat_times(t_philo *philo, size_t i);
int		ft_print(t_philo *philo, char *status);
void	ft_destroy_data(t_info *context);
void	ft_check_dead(t_info *context);
void	ft_init_data(t_info *context);
int		ft_set_data(t_info *context);
int		ft_take_forks(t_philo *philo);
int		ft_thinking(t_philo *philo);
int		ft_sleeping(t_philo *philo);
int		ft_eating(t_philo *philo);
size_t	ft_atol(const char *s);
int		ft_error_args(int ac);
void	*routine(void *arg);
size_t	ft_get_time(void);

#endif
