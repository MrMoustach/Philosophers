/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:02:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/29 12:37:47 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"
#include <string.h>


int main()
{
	t_clist	*tmp;
	t_philo	*philo;
	t_table	table;

	table.count = 0;
	table.philos = NULL;
	table = add_philo(table);
	table = add_philo(table);
	table = add_philo(table);
	table = add_philo(table);
	table = add_philo(table);
	table = add_philo(table);
	table = add_philo(table);
	tmp = table.philos;
	while (tmp->next)
	{
		printf("Philo : %d index : %d\n",tmp->content.id, tmp->index);
		tmp = tmp->next;
		if (tmp == table.philos)
			break ;
	}
	
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
