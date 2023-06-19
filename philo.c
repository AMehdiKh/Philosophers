/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:25:46 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/19 15:31:51 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Your program should take the following arguments:\n");
		printf("* number_of_philosophers.\n");
		printf("* time_to_die (in milliseconds).\n");
		printf("* time_to_eat (in milliseconds).\n");
		printf("* time_to_sleep (in milliseconds).\n");
		printf("* number_of_times_each_philosopher_must_eat "
			"(optional argumen).\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
