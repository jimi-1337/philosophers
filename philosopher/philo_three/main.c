/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:42:01 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/12 19:35:49 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void	ft_start(int c)
{
	int index;

	index = c;
	ft_display_message("started\n", 1 + index);
	ft_lunch_thread(index);
	while (g_philos[index].died == 0 &&
	(g_philos[index].times_eat < g_philos[index].max))
	{
		sem_wait(g_lock);
		if (ft_check_one() == 1)
		{
			sem_post(g_lock);
			break ;
		}
		ft_work(index);
		ft_print_max_time(index);
		ft_display_message("is sleeping\n", g_philos[index].index);
		sem_post(g_lock);
		if (ft_sleep(index))
			break ;
		ft_display_message("is thinking\n", g_philos[index].index);
	}
	if (g_philos[index].died == 1)
		ft_kill_all();
	exit(1);
}

int		main(int ac, char **av)
{
	sem_unlink("g_write");
	g_write = sem_open("g_write", O_CREAT | O_EXCL, 0644, 1);
	if (ac < 5 || ac > 6)
		return (ft_exit("bad arduments\n"));
	if (init(ac, av))
		return (ft_free() && ft_exit("error init\n"));
	if (start_threads())
		return (ft_free() && ft_exit("error starting\n"));
	sem_unlink("g_lock");
	ft_kill_all();
	return (0);
}
