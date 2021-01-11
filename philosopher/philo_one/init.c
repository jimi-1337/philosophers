/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:26:28 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/11 19:29:19 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_one.h"

int		init_philos(void)
{
	int i;

	i = 0;
	if (!(g_philos = (t_philo*)malloc(sizeof(t_philo) * g_data.amount)))
		return (1);
	while (i < g_data.amount)
	{
		g_philos[i].index = i + 1;
		g_philos[i].fork = 1;
		g_philos[i].right = (i + 1) % g_data.amount;
		g_philos[i].die = g_data.time_to_die;
		g_philos[i].sleep = g_data.time_to_sleep;
		g_philos[i].eat = g_data.time_to_eat;
		g_philos[i].died = 0;
		g_philos[i].times_eat = 0;
		g_philos[i].last_meal = ft_time();
		g_philos[i].check = 0;
		pthread_mutex_init(&g_philos[i].lock, NULL);
		if (g_data.must_eat_count)
			g_philos[i].max = g_data.must_eat_count;
		else
			g_philos[i].max = 1;
		i++;
	}
	return (0);
}

int		init(int ac, char **av)
{
	g_data.amount = ft_atoi(av[1]);
	g_data.time_to_die = ft_atoi(av[2]);
	g_data.time_to_eat = ft_atoi(av[3]);
	g_data.time_to_sleep = ft_atoi(av[4]);
	g_times_eat_check = 0;
	if (ac == 6)
	{
		g_data.must_eat_count = ft_atoi(av[5]);
		g_times_eat_check = 1;
	}
	else
		g_data.must_eat_count = 0;
	if (g_data.amount < 2 || g_data.amount > 200 || g_data.time_to_die < 60
		|| g_data.time_to_eat < 60 || g_data.time_to_sleep < 60
		|| g_data.must_eat_count < 0)
		return (1);
	if (init_philos())
		return (ft_exit("ERROR MALLOC\n"));
	return (0);
}
