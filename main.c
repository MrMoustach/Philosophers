/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:20:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/05 15:58:20 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

t_table	g_table;

void	express(t_philo	philo, struct timeval tv)
{
	pthread_mutex_lock(&g_table.print);
	usleep(10);
	if (philo.status == SLEEPING)
		printf("\033[32;1mat : %lld Philo %d is sleeping\033[0m\n", (long long)tv.tv_usec, philo.id);
	if (philo.status == THINKING)
		printf("\033[35;1mat : %lld Philo %d is thinking\033[0m\n", (long long)tv.tv_usec, philo.id);
	if (philo.status == EATING)
		printf("\033[31;1mat : %lld Philo %d is eating\033[0m\n", (long long)tv.tv_usec, philo.id);
	pthread_mutex_unlock(&g_table.print);
}

void	print_status()
{
	struct timeval tv;
	t_clist	*tmp;
	pthread_mutex_lock(&g_table.print);
	gettimeofday(&tv, NULL);
	printf("time to sleep : %d\n", g_table.time_to_sleep);
	printf("time to eat : %d\n", g_table.time_to_eat);
	printf("time to die : %d\n", g_table.time_to_die);
	printf("time now : %d\n", tv.tv_usec);
	printf("id        status         last ate     last slept     n_ate      n_slept\n");
	tmp = g_table.philos;
	while (tmp->next)
	{
		printf("%5d %5d %15d %15d %10d %10d\n",tmp->content->id, tmp->content->status, tmp->content->last_ate, tmp->content->last_slept, tmp->content->n_ate, tmp->content->n_slept);
		tmp = tmp->next;
		if (tmp == g_table.philos)
			break ;
	}
	pthread_mutex_unlock(&g_table.print);

}

void	*routine(void *contents)
{
	t_philo			*philo;
	int				fork_index;
	struct timeval	tv;
	
	philo = (t_philo *)contents;
	fork_index = philo->id % g_table.count ;
	while (1)
	{
		if (philo->n_ate)
		{
			gettimeofday(&tv, NULL);
			philo->status = SLEEPING;
			sleep(g_table.time_to_sleep);
			philo->n_slept++;
			philo->last_slept = tv.tv_usec + g_table.time_to_sleep;
			express(*philo,tv);
		}
		pthread_mutex_lock(&g_table.forks[philo->id - 1]);
		pthread_mutex_lock(&g_table.forks[fork_index]);
		gettimeofday(&tv, NULL);
		philo->status = EATING;
		express(*philo, tv);
		sleep(g_table.time_to_eat);
		philo->n_ate++;
		philo->last_ate = tv.tv_usec + g_table.time_to_eat;
		pthread_mutex_unlock(&g_table.forks[philo->id - 1]);
		pthread_mutex_unlock(&g_table.forks[fork_index]);
	}
	return (contents);
}

t_table	init_table(int ac, char *av[])
{
	t_table	table;
	int	i;

	table.error = 0;
	table.philos = NULL;
	if (!(ac == 6 || ac == 5))
	{
		table.error = -1;
		return (table);
	}
	table.count = try_parse_int(av[1], &table.error);
	table.time_to_die = try_parse_int(av[2], &table.error);
	table.time_to_eat = try_parse_int(av[3], &table.error);
	table.time_to_sleep = try_parse_int(av[4], &table.error);
	if (ac == 6)
		table.max_n_eat = try_parse_int(av[5], &table.error);
	if (table.error == 0)
	{
		pthread_mutex_init(&g_table.print, NULL);	
		table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table.count);
	}
	return (table);
}

int	main(int ac, char **av)
{
	int	i;

	g_table = init_table(ac, av);
	if (g_table.error)
	{
		write (2, "Error\n", 7);
		return (1);
	}
	i = 0;
	while (i < g_table.count)
		g_table = add_philo(g_table, i++);
	while (1)
	{
		print_status();
		sleep(1);
	}
}