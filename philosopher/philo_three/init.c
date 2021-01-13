/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:26:28 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/12 19:34:00 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	sem_unlink("g_lock");
	g_lock = sem_open("g_lock", O_CREAT | O_EXCL, 0644, g_data.amount / 2);
	if (!(g_ids = (int *)malloc(sizeof(int) * g_data.amount)))
		return (ft_exit("ERROR MALLOC\n"));
	if (init_philos())
		return (ft_exit("ERROR MALLOC\n"));
	return (0);
}

void	ft_work(int index)
{
	g_philos[index].last_meal = ft_time();
	ft_display_message("has taken a fork\n", g_philos[index].index);
	ft_display_message("is eating\n", g_philos[index].index);
	usleep(g_philos[index].eat * 1000);
	if (g_times_eat_check)
		g_philos[index].times_eat++;
}

int		ft_check_one(void)
{
	int i;

	i = 0;
	while (i < g_data.amount)
	{
		if (g_philos[i].died)
			return (1);
		i++;
	}
	return (0);
}
