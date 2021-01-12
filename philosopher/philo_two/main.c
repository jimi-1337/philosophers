/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:42:01 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/12 17:52:31 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

sem_t		*g_write;

void	ft_display_message(char *str, int index)
{
	sem_wait(g_write);
	ft_putnbr_fd(ft_time_test(ft_time(), g_data.start), 1);
	write(1, " ", 1);
	ft_putnbr_fd(index, 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	sem_post(g_write);
}

int		ft_check_max(void)
{
	int i;

	i = 0;
	while (i < g_data.amount)
	{
		if (g_philos[i].times_eat == g_data.must_eat_count && g_times_eat_check)
			return (0);
		i++;
	}
	return (1);
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
			g_data.time_to_die && ft_check_max())
			{
				g_philos[i].died = 1;
				ft_display_message("is died\n", g_philos[i].index);
				return (1);
			}
			check = ft_print_max_time(check, i);
			i++;
		}
	}
	return (0);
}

void	ft_start(int c)
{
	int index;
	int start;

	index = c;
	start = 0;
	while (g_philos[index].died == 0 &&\
	(g_philos[index].times_eat < g_philos[index].max))
	{
		sem_wait(g_lock);
		if (ft_check_one() == 1)
		{
			sem_post(g_lock);
			break ;
		}
		ft_work(index);
		sem_post(g_lock);
		if (g_times_eat_check && g_philos[index].times_eat >=
		g_data.must_eat_count)
			break ;
		ft_display_message("is sleeping\n", g_philos[index].index);
		if (ft_sleep(index))
			break ;
		ft_display_message("is thinking\n", g_philos[index].index);
	}
}

int		main(int ac, char **av)
{
	sem_unlink("write");
	g_write = sem_open("write", O_CREAT | O_EXCL, 0644, 1);
	if (ac < 5 || ac > 6)
		return (ft_exit("bad arduments\n"));
	if (init(ac, av))
		return (ft_free() && ft_exit("error init\n"));
	if (start_threads())
		return (ft_free() && ft_exit("error starting\n"));
	ft_check_philos();
	ft_destr();
	return (0);
}
