/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:02:03 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/13 16:05:04 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_sleep_int(int time_one, int x, int index)
{
	int i;

	i = 0;
	while (i < x)
	{
		usleep((int)(time_one / x) * 1000);
		if (ft_time_test(ft_time(), g_philos[index].last_meal) >
		g_data.time_to_die)
		{
			g_philos[index].died = 1;
			ft_display_message(" died\n", g_philos[index].index);
			return (1);
		}
	}
	return (0);
}

int		ft_sleep(int index)
{
	int		x;
	float	y;
	int		i;
	int		time_one;

	i = 0;
	x = (int)(g_data.time_to_sleep / g_data.time_to_die);
	y = g_data.time_to_sleep % g_data.time_to_die;
	time_one = g_data.time_to_sleep;
	if (ft_sleep_int(time_one, x, index))
		return (1);
	usleep((int)((y) * 1000));
	if (ft_time_test(ft_time(), g_philos[index].last_meal) > g_data.time_to_die)
	{
		g_philos[index].died = 1;
		ft_display_message("died\n", g_philos[index].index);
		return (1);
	}
	return (0);
}

void	ft_kill_all(void)
{
	int i;

	i = 0;
	while (i < g_data.amount)
	{
		if (g_ids[i] != 0)
			kill(g_ids[i], SIGKILL);
		i++;
	}
	free(g_philos);
	free(g_ids);
}
