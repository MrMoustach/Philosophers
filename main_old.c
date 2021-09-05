/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:02:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/04 19:37:46 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"
#include <string.h>

t_table	g_table;

void *routine(void *content)
{
	t_philo *philo;
	int		index;
	struct timeval tv;

	
	philo = ((t_philo *)content);
	while (1)
	{
		index = ((philo->id - 2) + g_table.count) % g_table.count;
		if (philo->n_ate)
		{
			gettimeofday(&tv, NULL);
			philo->status = SLEEPING;
			printf("\033[32;1mat : %lld Philo %d is sleeping\033[0m\n", (long long)tv.tv_usec, philo->id);
			philo->n_slept++;
			usleep(g_table.time_to_sleep);
			gettimeofday(&tv, NULL);
			philo->status = THINKING;
			printf("\033[35;1mat : %lld Philo %d is thinking\033[0m\n", (long long)tv.tv_usec, philo->id);
			philo->n_thought++;
			usleep(g_table.time_to_die - g_table.time_to_sleep);
		}
		pthread_mutex_lock(&g_table.forks[philo->id - 1]);
		pthread_mutex_lock(&g_table.forks[index]);
		gettimeofday(&tv, NULL);
		philo->status = EATING;
		printf("\033[31;1mat : %lld Philo %d is eating\033[0m\n", (long long)tv.tv_usec, philo->id);
		philo->n_ate++;
		philo->last_ate = tv.tv_usec;
		usleep(g_table.time_to_eat);
		pthread_mutex_unlock(&g_table.forks[philo->id - 1]);
		pthread_mutex_unlock(&g_table.forks[index]);
	}
	return (NULL);
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
		table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table.count);
	return (table);
}

int main(int ac, char **av)
{
	t_clist	*tmp;
	t_philo	*philo;
	struct timeval tv;
	int	i;
	int	count;
	
	g_table = init_table(ac, av);
	if (g_table.error != 0)
	{
		write (2, "Error\n", 7);
		return (1);
	}
	i = 0;
	while (i < g_table.count)
	{
		g_table = add_philo(g_table, i);
		pthread_mutex_init(&g_table.forks[i++], NULL);
		// sleep(1);
	}
	tmp = g_table.philos;
	while (tmp->next)
	{
		pthread_create(&(tmp->content->tid), NULL, &routine, (void *)tmp->content);
		tmp = tmp->next;
		if (tmp == g_table.philos)
			break ;
	}
	tmp = g_table.philos;
	while (tmp->next)
	{
		gettimeofday(&tv, NULL);
		// printf("philo %d ate : %d last meal : %d time to die %d\n", tmp->content->id, tmp->content->n_ate, (tv.tv_usec - tmp->content->last_ate), g_table.time_to_die);
		if (tmp->content->n_ate > 0 && (tv.tv_usec - tmp->content->last_ate) > g_table.time_to_die)
		{
			usleep(5);
			printf("at: %d Philo %d died\n", tv.tv_usec, tmp->content->id);
			exit(1);
		}
		tmp = tmp->next;
	}
	tmp = g_table.philos;
	while (tmp->next)
	{
		pthread_join(tmp->content->tid, NULL);
		pthread_mutex_destroy(&tmp->content->the_fork);
		gettimeofday(&tv, NULL);
		printf("added at :%lld | Philo : %d index : %d\n", (long long)tmp->content->time_added, tmp->content->id, tmp->index);
		tmp = tmp->next;
		if (tmp == g_table.philos)
			break ;
	}
	// pthread_mutex_destroy(&lock);
}

// pthread_t tid[2];
// int counter;
// pthread_mutex_t lock;


// int test()
// {
// 	pthread_mutex_lock(&lock);
// 	counter += 1;
// 	printf("\n Job %d has started\n", counter);
//     printf("lmao %d", counter);    
// 	pthread_mutex_unlock(&lock);\
// 	return (0);
// }

// void* trythis(void* arg)
// {

// 	unsigned long i = 0;
// 	sleep(2);
//     test();

// 	printf("\n Job %d has finished\n", counter);


// 	return NULL;
// }

// int main(void)
// {
// 	int i = 0;
// 	int error;

// 	if (pthread_mutex_init(&lock, NULL) != 0) {
// 		printf("\n mutex init has failed\n");
// 		return 1;
// 	}

// 	while (i < 2) {
// 		error = pthread_create(&(tid[i]),
// 							NULL,
// 							&trythis, NULL);
// 		if (error != 0)
// 			printf("\nThread can't be created :[%s]",
// 				strerror(error));
// 		i++;
// 	}

// 	pthread_join(tid[0], NULL);
// 	pthread_join(tid[1], NULL);
// 	pthread_mutex_destroy(&lock);

// 	return 0;
// }
