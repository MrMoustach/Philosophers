/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:20:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/14 18:02:07 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"


void	express(t_philo	philo, size_t time)
{
	pthread_mutex_lock(&g_table.print);
	if (philo.status == FORK_1)
		printf("\033[31;1mat : %zu Philo %d took his fork\033[0m\n", time, philo.id);
	if (philo.status == FORK_2)
		printf("\033[31;1mat : %zu Philo %d took the second fork\033[0m\n", time, philo.id);
	if (philo.status == SLEEPING)
		printf("\033[32;1mat : %zu Philo %d is sleeping\033[0m\n", time, philo.id);
	if (philo.status == THINKING)
		printf("\033[35;1mat : %zu Philo %d is thinking\033[0m\n", time, philo.id);
	if (philo.status == EATING)
		printf("\033[31;1mat : %zu Philo %d is eating\033[0m\n", time, philo.id);
	pthread_mutex_unlock(&g_table.print);
}

void	print_status()
{
	t_clist	*tmp;

	pthread_mutex_lock(&g_table.print);
	printf("time to sleep : %d\n", g_table.time_to_sleep);
	printf("time to eat : %d\n", g_table.time_to_eat);
	printf("time to die : %d\n", g_table.time_to_die);
	printf("time now : %zu\n", get_time());
	printf("id        status         last ate     last slept     n_ate      n_slept\n");
	tmp = g_table.philos;
	while (tmp->next)
	{
		printf("%5d %5d %15zu %15zu %10d %10d\n",tmp->content->id, tmp->content->status, tmp->content->last_ate, tmp->content->last_slept, tmp->content->n_ate, tmp->content->n_slept);
		tmp = tmp->next;
		if (tmp == g_table.philos)
			break ;
	}
	pthread_mutex_unlock(&g_table.print);

}

// void	*routine(void *contents)
// {
// 	t_philo			*philo;
// 	int				fork_index;
// 	struct timeval	tv;
// 	struct timeval	ntv;
	
// 	philo = (t_philo *)contents;
// 	fork_index = philo->id % g_table.count ;
// 	while (1)
// 	{
// 		if (philo->status == DEAD)
// 			continue;
// 		if (philo->n_ate || philo->id % 2)
// 		{
// 			gettimeofday(&tv, NULL);
// 			philo->status = SLEEPING;
// 			express(*philo,tv);
// 			gettimeofday(&ntv, NULL);
// 			philo_sleep(g_table.time_to_sleep);
// 			philo->n_slept++;
// 			philo->last_slept = tv.tv_usec + g_table.time_to_sleep;
// 			gettimeofday(&tv, NULL);
// 			philo->status = THINKING;
// 			express(*philo, tv);
// 			gettimeofday(&ntv, NULL);
// 			philo_sleep(g_table.time_to_eat - g_table.time_to_sleep - (ntv.tv_usec - tv.tv_usec));
// 			philo->n_thought++;
// 			philo->last_thought = tv.tv_usec + (g_table.time_to_eat - g_table.time_to_sleep);
// 		}
// 		pthread_mutex_lock(&g_table.forks[philo->id - 1]);
// 		philo->status = FORK_1;
// 		gettimeofday(&tv, NULL);
// 		express(*philo, tv);
// 		pthread_mutex_lock(&g_table.forks[fork_index]);
// 		gettimeofday(&tv, NULL);
// 		philo->status = FORK_2;
// 		express(*philo, tv);
// 		philo->status = EATING;
// 		express(*philo, tv);
// 		philo_sleep(g_table.time_to_eat);
// 		philo->n_ate++;
// 		philo->last_ate = tv.tv_usec + g_table.time_to_eat;
// 		pthread_mutex_unlock(&g_table.forks[philo->id - 1]);
// 		pthread_mutex_unlock(&g_table.forks[fork_index]);
// 	}
// 	return (contents);
// }

void *routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *) content;
	while (1)
	{
		if (philo->id % 2 == 0 || philo->n_ate)
			philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
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
	table.max_n_eat = -1;
	if (ac == 6)
		table.max_n_eat = try_parse_int(av[5], &table.error);
	table.started_at = 0;
	if (table.error == 0)
	{
		pthread_mutex_init(&g_table.print, NULL);	
		table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table.count);
	}
	return (table);
}

int	main(int ac, char **av)
{
	int		i;
	t_clist	*tmp;

	g_table = init_table(ac, av);
	if (g_table.error)
	{
		write (2, "Error\n", 7);
		return (1);
	}
	i = 0;
	while (i < g_table.count)
		g_table = add_philo(g_table, i++);
	tmp = g_table.philos;
	g_table.started_at = get_time();
	while (tmp->next)
	{
		pthread_create(&(tmp->content->tid), NULL, &routine, tmp->content);
		usleep(100);
		tmp = tmp->next;
		if (tmp == g_table.philos)
			break ;
	}
	while (1)
	{
		tmp = g_table.philos;
		i = 0;
		while (tmp->next)
		{
			if (tmp->content->n_ate >= g_table.max_n_eat)
				i++;
			if ((get_time() - tmp->content->last_ate >= g_table.time_to_die) && tmp->content->status != EATING)
			{	
				tmp->content->status = DEAD;
				printf("philo %d died\n", tmp->content->id);
				exit (1);
			}
			tmp = tmp->next;
			if (tmp == g_table.philos)
				break ;
		}
		if (i == g_table.count)
		{
			printf("Completed at %zu\n", get_time());	
			print_status();
			exit (1);
		}

	}
}