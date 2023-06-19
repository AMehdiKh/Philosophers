/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:58:33 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/19 21:52:20 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_switching
{
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_times;
	t_philo	*philo;
}	t_switching;

#endif
