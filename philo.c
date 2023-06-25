/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:25:46 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/25 10:53:28 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

int	ft_eating(t_switch *context)
{
	pthread_mutex_lock(&context->eating);
	if (context->death)
		return (pthread_mutex_unlock(&context->eating), EXIT_FAILURE);
	context->philo->last_meal = ft_time_ms(&context->philo->time);
	printf("%d %d has taken a fork\n", context->philo->last_meal);
	printf("%d %d is eating\n", ft_time_ms(&context->philo->time));
	while (ft_time_ms(&context->philo->time)
		< (context->philo->last_meal + context->t_eat) && !is_dead(context))
		;
	if (context->death)
		return (pthread_mutex_unlock(&context->eating), EXIT_FAILURE);
	return (pthread_mutex_unlock(&context->eating), EXIT_SUCCESS);
}

int	ft_sleeping(t_switch *context)
{
	pthread_mutex_lock(&context->sleeping);
	if (context->death)
		return (pthread_mutex_unlock(&context->sleeping), EXIT_FAILURE);
	printf("%d %d is sleeping\n", ft_time_ms(&context->philo->time));
	while (ft_time_ms(&context->philo->time)
		< (context->philo->last_meal + context->t_eat + context->t_sleep)
		&& !is_dead(context))
		;
	if (context->death)
		return (pthread_mutex_unlock(&context->sleeping), EXIT_FAILURE);
	printf("%d %d is thinking\n", ft_time_ms(&context->philo->time));
	return (pthread_mutex_unlock(&context->sleeping), EXIT_SUCCESS);
}

int	is_dead(t_switch *context)
{
	size_t	death_time;

	death_time = ft_time_ms(&context->philo->time);
	if (death_time >= (context->philo->last_meal + context->t_die))
	{
		pthread_mutex_lock(&context->died);
		if (!context->death)
		{
			context->death = 1;
			printf("%d %d died\n", death_time);
		}
		return (pthread_mutex_unlock(&context->died), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_switch	*context;
	size_t		id;		

	context = arg;
	id = context->philoid;
	while (!context->death)
	{
		if (ft_eating(context))
			return (NULL);
		if (ft_sleeping(context))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_switch	*context;
	int			i;

	context = malloc(sizeof(t_switch));
	if (!context)
		return (EXIT_FAILURE);
	if (ft_check_args(memset(context, 0, sizeof(t_switch)), ac, av))
		return (free(context), EXIT_FAILURE);
	context->philo = malloc(sizeof(t_philo) * context->n_philo);
	if (!context->philo)
		return (free(context), EXIT_FAILURE);
	pthread_mutex_init(&context->eating, NULL);
	pthread_mutex_init(&context->sleeping, NULL);
	pthread_mutex_init(&context->died, NULL);
	i = -1;
	while (++i < context->n_philo)
	{
		
		pthread_create(&context->philo[i].thread, NULL, routine, context);
	}
	i = -1;
	while (++i < context->n_philo)
		pthread_join(context->philo[i].thread, NULL);
	pthread_mutex_destroy(&context->eating);
	pthread_mutex_destroy(&context->sleeping);
	pthread_mutex_destroy(&context->died);
	return (free(context->philo), free(context), EXIT_SUCCESS);
}
