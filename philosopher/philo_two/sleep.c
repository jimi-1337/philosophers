/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:02:03 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/12 17:33:30 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
			ft_display_message("%d died\n", g_philos[index].index);
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
		ft_display_message("is died\n", g_philos[index].index);
		return (1);
	}
	return (0);
}
