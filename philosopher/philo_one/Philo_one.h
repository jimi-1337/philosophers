/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:40:12 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/11 19:33:51 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int				index;
	int				fork;
	int				right;
	int				die;
	int				sleep;
	int				eat;
	int				died;
	int				times_eat;
	int				times_eat_check;
	int				max;
	int				check;
	struct timeval	last_meal;
	pthread_mutex_t	lock;
}				t_philo;

typedef struct	s_data
{
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	struct timeval	start;
}				t_data;

void				ft_destr();
int					ft_sleep(int index);
int					ft_time_test(struct timeval ret, struct timeval philotime);
struct timeval		ft_time();
void				ft_display_message(char *str, int index);
int					ft_strlen(char *str);
int					ft_exit(char *str);
int					ft_atoi(char *str);
void				ft_putnbr_fd(int n, int fd);
void				*ft_lunch(void *i);
void				ft_start(int c);
int					init(int ac, char **av);
int					ft_free(void);
int					start_threads(void);

pthread_mutex_t		g_lock;
t_philo				*g_philos;
t_data				g_data;
int					g_times_eat_check;
#endif