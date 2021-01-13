/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:42:01 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/13 17:15:51 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_display_message(char *str, int index)
{
	pthread_mutex_lock(&g_write);
	ft_putnbr_fd(ft_time_test(ft_time(), g_data.start), 1);
	write(1, " ", 1);
	ft_putnbr_fd(index, 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&g_write);
}

int		ft_check_philos(void)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (1)
	{
		usleep(10);
		i = 0;
		while (i < g_data.amount)
		{
			if (check >= g_data.amount)
				return (1);
			if (ft_time_test(ft_time(), g_philos[i].last_meal) >\
			g_data.time_to_die)
			{
				g_philos[i].died = 1;
				ft_display_message("died\n", g_philos[i].index);
				return (1);
			}
			check = ft_print_max_time(check, i);
			i++;
		}
	}
	return (0);
}

int		ft_work(int index)
{
	g_philos[index].fork = 2;
	g_philos[g_philos[index].right].fork = 0;
	g_philos[index].last_meal = ft_time();
	ft_display_message("has taken a fork\n", g_philos[index].index);
	ft_display_message("is eating\n", g_philos[index].index);
	usleep(g_data.time_to_eat * 1000);
	g_philos[index].fork = 1;
	g_philos[g_philos[index].right].fork = 1;
	if (g_times_eat_check)
		g_philos[index].times_eat++;
	pthread_mutex_unlock(&g_philos[index].lock);
	pthread_mutex_unlock(&g_philos[g_philos[index].right].lock);
	if (g_times_eat_check && g_philos[index].times_eat >=
	g_data.must_eat_count)
		return (1);
	ft_display_message("is sleeping\n", g_philos[index].index);
	if (ft_sleep(index))
		return (1);
	ft_display_message("is thinking\n", g_philos[index].index);
	return (0);
}

void	ft_start(int c)
{
	int index;

	index = c;
	while (g_philos[index].died == 0 && \
	(g_philos[index].times_eat < g_philos[index].max))
	{
		pthread_mutex_lock(&g_philos[index].lock);
		pthread_mutex_lock(&g_philos[g_philos[index].right].lock);
		if (g_philos[index].fork == 1 && \
		g_philos[g_philos[index].right].fork == 1 && g_philos[index].died != 1)
		{
			if (ft_work(index))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&g_philos[index].lock);
			pthread_mutex_unlock(&g_philos[g_philos[index].right].lock);
		}
	}
}

int		main(int ac, char **av)
{
	pthread_mutex_init(&g_write, NULL);
	if (ac < 5 || ac > 6)
		return (ft_exit("bad arduments\n"));
	if (init(ac, av))
		return (ft_free() && ft_exit("error init\n"));
	if (start_threads())
		return (ft_free() && ft_exit("error starting\n"));
	ft_check_philos();
	pthread_mutex_lock(&g_write);
	pthread_mutex_unlock(&g_write);
	ft_destr();
	return (0);
}
