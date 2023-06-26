/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:25:46 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/26 03:15:06 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	ft_eating(t_philo *philo, size_t *last_meal)
{
	pthread_mutex_lock(&context->eating);
	is_dead(context, id, last_meal);
	if (context->died)
		return (pthread_mutex_unlock(&context->eating), EXIT_FAILURE);
	*last_meal = ft_get_time();
	printf("%zu %zu has taken a fork\n", *last_meal, id);
	printf("%zu %zu is eating\n", ft_get_time(), id);
	while (ft_get_time()
		< (*last_meal + context->t_eat) && !is_dead(context, id, last_meal))
		;
	if (context->died)
		return (pthread_mutex_unlock(&context->eating), EXIT_FAILURE);
	return (pthread_mutex_unlock(&context->eating), EXIT_SUCCESS);
}

int	ft_sleeping(t_switch *context, size_t id, size_t *last_meal)
{
	pthread_mutex_lock(&context->sleeping);
	is_dead(context, id, last_meal);
	if (context->died)
		return (pthread_mutex_unlock(&context->sleeping), EXIT_FAILURE);
	printf("%zu %zu is sleeping\n", ft_get_time(), id);
	while (ft_get_time()
		< (*last_meal + context->t_eat + context->t_sleep)
		&& !is_dead(context, id, last_meal))
		;
	if (context->died)
		return (pthread_mutex_unlock(&context->sleeping), EXIT_FAILURE);
	printf("%zu %zu is thinking\n", ft_get_time(), id);
	return (pthread_mutex_unlock(&context->sleeping), EXIT_SUCCESS);
}

int	is_dead(t_switch *context, size_t id, size_t *last_meal)
{
	size_t	death_time;

	death_time = ft_get_time();
	if (death_time >= (*last_meal + context->t_die))
	{
		pthread_mutex_lock(&context->death);
		if (!context->died)
		{
			context->died = 1;
			printf("%zu %zu died\n", death_time, id);
		}
		return (pthread_mutex_unlock(&context->death), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	size_t		last_meal;
	size_t		i;

	philo = arg;
	last_meal = ft_get_time();
	i = 0;
	while (1)
	{
		if (ft_eating(philo, id, &last_meal))
			return (NULL);
		if (ft_sleeping(context, id, &last_meal))
			return (NULL);
		if (context->n_times && (i >= context->n_times))
			return (NULL);
		++i;
	}
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
	context->forks = malloc(sizeof(pthread_mutex_t) * context->n_philo);
	if (!context->forks)
		return (free(context->philo), free(context), EXIT_FAILURE);
	i = -1;
	while (++i < context->n_philo)
		pthread_mutex_init(&context->forks[i], NULL);
	i = -1;
	while (++i < context->n_philo)
	{
		context->philo[i].n_philo = context->n_philo;
		context->philo[i].t_die = context->t_die;
		context->philo[i].t_eat = context->t_eat;
		context->philo[i].t_sleep = context->t_sleep;
		context->philo[i].n_times = context->n_times;
		context->philo[i].context = context;
	}
	i = -1;
	while (++i < context->n_philo)
	{
		context->philo[i].id = i;
		pthread_create(&context->philo[i].thread, NULL, routine, &context->philo[i]);
		usleep(5000);
	}
	i = -1;
	while (++i < context->n_philo)
		pthread_join(context->philo[i].thread, NULL);
	pthread_mutex_destroy(&context->eating);
	pthread_mutex_destroy(&context->sleeping);
	pthread_mutex_destroy(&context->death);
	return (free(context->forks), free(context->philo), free(context), EXIT_SUCCESS);
}
