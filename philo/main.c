/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:44:43 by ael-khel          #+#    #+#             */
/*   Updated: 2023/08/13 21:09:59 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead_philo(t_switch *context, size_t i)
{
	size_t	current_time;
	size_t	last_meal;

	pthread_mutex_lock(&context->meal);
	current_time = ft_get_time();
	last_meal = context->philo[i].last_meal;
	if (context->philo[i].life && (current_time - last_meal) >= context->t_die)
	{
		pthread_mutex_unlock(&context->meal);
		pthread_mutex_lock(&context->print);
		context->died = 1;
		printf("%zu %zu died\n", current_time - context->philo[i].start,
			context->philo[i].id);
		pthread_mutex_unlock(&context->print);
		return (EXIT_FAILURE);
	}
	return (pthread_mutex_unlock(&context->meal), EXIT_SUCCESS);
}

void	ft_check_dead(t_switch *context)
{
	size_t	id;

	id = 0;
	while (1)
	{
		if (ft_dead_philo(context, id))
			return ;
		if (context->n_philo)
		{
			pthread_mutex_lock(&context->meal);
			if (context->total_eat == context->n_philo)
			{
				pthread_mutex_unlock(&context->meal);
				return ;
			}
			pthread_mutex_unlock(&context->meal);
		}
		id = (id + 1) % context->n_philo;
		usleep(50);
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;
	size_t		i;

	philo = arg;
	pthread_mutex_lock(&philo->context->meal);
	philo->start = ft_get_time();
	philo->last_meal = philo->start;
	pthread_mutex_unlock(&philo->context->meal);
	i = 1;
	while (1)
	{
		if (ft_thinking(philo))
			return (NULL);
		if (ft_take_forks(philo))
			return (NULL);
		if (ft_eating(philo))
			return (NULL);
		if (ft_sleeping(philo))
			return (NULL);
		if (ft_eat_times(philo, i))
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
		return (EXIT_FAILURE);
	if (ft_set_data(context))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < (int)context->n_philo)
	{
		pthread_create(&context->philo[i].thread, NULL, routine,
			&context->philo[i]);
		usleep(100);
	}
	ft_check_dead(context);
	ft_destroy_data(context);
	return (EXIT_SUCCESS);
}
