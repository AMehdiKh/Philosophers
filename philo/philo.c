/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:25:46 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/29 00:10:25 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo->last_meal = ft_get_time();
	ft_print(philo, philo->last_meal, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, ft_get_time(), "has taken a fork");
	ft_print(philo, ft_get_time(), "is eating");
	usleep((philo->t_eat / 2) * 1000);
	while (ft_get_time() - philo->last_meal < philo->t_eat)
		;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleeping(t_philo *philo)
{
	ft_print(philo, ft_get_time(), "is sleeping");
	usleep((philo->t_sleep / 2) * 1000);
	while (ft_get_time() - (philo->last_meal + philo->t_eat) < philo->t_sleep)
		;
}

void	*routine(void *arg)
{
	t_philo		*philo;
	size_t		i;

	philo = arg;
	philo->start = ft_get_time();
	philo->last_meal = philo->start;
	i = 1;
	while (1)
	{
		ft_print(philo, ft_get_time(), "is thinking");
		ft_eating(philo);
		ft_sleeping(philo);
		if (philo->n_times && (i >= philo->n_times))
		{
			pthread_mutex_lock(&philo->context->check);
			philo->life = 0;
			++philo->context->total_eat;
			pthread_mutex_unlock(&philo->context->check);
			return (NULL);
		}
		++i;
	}
	return (NULL);
}

void	is_dead(t_switch *context)
{
	size_t	death_time;
	size_t	i;

	i = 0;
	while (1)
	{
		death_time = ft_get_time();
		pthread_mutex_lock(&context->check);
		if (death_time - context->philo[i].last_meal >= context->t_die
			&& context->philo[i].life)
		{
			// ft_print(&context->philo[i], death_time, "died");
			pthread_mutex_lock(&context->print);
			context->died = 1;
			printf("%zu %zu died\n", death_time - context->philo[i].start, context->philo[i].id);
			pthread_mutex_unlock(&context->print);
			pthread_mutex_unlock(&context->check);

			// pthread_mutex_destroy(&context->print);
			break ;
		}
		pthread_mutex_unlock(&context->check);
		pthread_mutex_lock(&context->check);
		if (context->n_philo)
		{
			if (context->total_eat == (int)context->n_philo)
			{
				pthread_mutex_unlock(&context->check);
				break ;
			}
		}
		pthread_mutex_unlock(&context->check);

		i = (i + 1) % context->n_philo;
		usleep(1000);
	}
}
int	main(int ac, char **av)
{
	t_switch	*context;
	int			i;

	context = malloc(sizeof(t_switch));
	if (!context)
		return (EXIT_FAILURE);
	if (ft_set_data(context, ac, av))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < (int)context->n_philo)
	{
		pthread_create(&context->philo[i].thread, NULL, routine,
			&context->philo[i]);
		usleep(100);
		// pthread_detach(context->philo[i].thread);
	}
	is_dead(context);
	i = -1;
	while (++i < (int)context->n_philo)
		pthread_mutex_destroy(&context->forks[i]);
	pthread_mutex_destroy(&context->check);
	pthread_mutex_destroy(&context->print);
	return (free(context->forks), free(context->philo), free(context),
		EXIT_SUCCESS);
}

void	ft_print(t_philo *philo, size_t time, char *status)
{
	pthread_mutex_lock(&philo->context->print);
	if (!philo->context->died)
		printf("%zu %zu %s\n", time - philo->start, philo->id, status);
	pthread_mutex_unlock(&philo->context->print);
}

